#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sbni_in_stats {int dummy; } ;
struct sbni_flags {int slow_mode; size_t rxl; int fixed_rxl; int /*<<< orphan*/  rate; int /*<<< orphan*/  mac_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  rate; int /*<<< orphan*/  rxl; } ;
struct net_local {int state; size_t cur_rxl_index; int /*<<< orphan*/  lock; TYPE_1__ csr1; int /*<<< orphan*/  delta_rxl; struct sbni_flags in_stats; } ;
struct net_device {int flags; scalar_t__ base_addr; int /*<<< orphan*/  dev_addr; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; int /*<<< orphan*/  ifr_ifru; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 scalar_t__ CSR1 ; 
 size_t DEF_RXL ; 
 int /*<<< orphan*/  DEF_RXL_DELTA ; 
 int EFAULT ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int FL_SLOW_MODE ; 
 int IFF_UP ; 
 int PR_RES ; 
#define  SIOCDEVEMANSIPATE 133 
#define  SIOCDEVENSLAVE 132 
#define  SIOCDEVGETINSTATS 131 
#define  SIOCDEVGHWSTATE 130 
#define  SIOCDEVRESINSTATS 129 
#define  SIOCDEVSHWSTATE 128 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_from_user (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  copy_to_user (int /*<<< orphan*/ ,struct sbni_flags*,int) ; 
 struct net_device* dev_get_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int emancipate (struct net_device*) ; 
 int enslave (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  memset (struct sbni_flags*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,char*) ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/ * rxl_tab ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sbni_ioctl( struct net_device  *dev,  struct ifreq  *ifr,  int  cmd )
{
	struct net_local  *nl = netdev_priv(dev);
	struct sbni_flags  flags;
	int  error = 0;

#ifdef CONFIG_SBNI_MULTILINE
	struct net_device  *slave_dev;
	char  slave_name[ 8 ];
#endif
  
	switch( cmd ) {
	case  SIOCDEVGETINSTATS :
		if (copy_to_user( ifr->ifr_data, &nl->in_stats,
					sizeof(struct sbni_in_stats) ))
			error = -EFAULT;
		break;

	case  SIOCDEVRESINSTATS :
		if (!capable(CAP_NET_ADMIN))
			return  -EPERM;
		memset( &nl->in_stats, 0, sizeof(struct sbni_in_stats) );
		break;

	case  SIOCDEVGHWSTATE :
		flags.mac_addr	= *(u32 *)(dev->dev_addr + 3);
		flags.rate	= nl->csr1.rate;
		flags.slow_mode	= (nl->state & FL_SLOW_MODE) != 0;
		flags.rxl	= nl->cur_rxl_index;
		flags.fixed_rxl	= nl->delta_rxl == 0;

		if (copy_to_user( ifr->ifr_data, &flags, sizeof flags ))
			error = -EFAULT;
		break;

	case  SIOCDEVSHWSTATE :
		if (!capable(CAP_NET_ADMIN))
			return  -EPERM;

		spin_lock( &nl->lock );
		flags = *(struct sbni_flags*) &ifr->ifr_ifru;
		if( flags.fixed_rxl )
			nl->delta_rxl = 0,
			nl->cur_rxl_index = flags.rxl;
		else
			nl->delta_rxl = DEF_RXL_DELTA,
			nl->cur_rxl_index = DEF_RXL;

		nl->csr1.rxl = rxl_tab[ nl->cur_rxl_index ];
		nl->csr1.rate = flags.rate;
		outb( *(u8 *)&nl->csr1 | PR_RES, dev->base_addr + CSR1 );
		spin_unlock( &nl->lock );
		break;

#ifdef CONFIG_SBNI_MULTILINE

	case  SIOCDEVENSLAVE :
		if (!capable(CAP_NET_ADMIN))
			return  -EPERM;

		if (copy_from_user( slave_name, ifr->ifr_data, sizeof slave_name ))
			return -EFAULT;
		slave_dev = dev_get_by_name(&init_net, slave_name );
		if( !slave_dev  ||  !(slave_dev->flags & IFF_UP) ) {
			netdev_err(dev, "trying to enslave non-active device %s\n",
				   slave_name);
			if (slave_dev)
				dev_put(slave_dev);
			return  -EPERM;
		}

		return  enslave( dev, slave_dev );

	case  SIOCDEVEMANSIPATE :
		if (!capable(CAP_NET_ADMIN))
			return  -EPERM;

		return  emancipate( dev );

#endif	/* CONFIG_SBNI_MULTILINE */

	default :
		return  -EOPNOTSUPP;
	}

	return  error;
}