#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int dummy; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
#define  EQL_EMANCIPATE 133 
#define  EQL_ENSLAVE 132 
#define  EQL_GETMASTRCFG 131 
#define  EQL_GETSLAVECFG 130 
#define  EQL_SETMASTRCFG 129 
#define  EQL_SETSLAVECFG 128 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int eql_emancipate (struct net_device*,int /*<<< orphan*/ ) ; 
 int eql_enslave (struct net_device*,int /*<<< orphan*/ ) ; 
 int eql_g_master_cfg (struct net_device*,int /*<<< orphan*/ ) ; 
 int eql_g_slave_cfg (struct net_device*,int /*<<< orphan*/ ) ; 
 int eql_s_master_cfg (struct net_device*,int /*<<< orphan*/ ) ; 
 int eql_s_slave_cfg (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eql_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	if (cmd != EQL_GETMASTRCFG && cmd != EQL_GETSLAVECFG &&
	    !capable(CAP_NET_ADMIN))
	  	return -EPERM;

	switch (cmd) {
		case EQL_ENSLAVE:
			return eql_enslave(dev, ifr->ifr_data);
		case EQL_EMANCIPATE:
			return eql_emancipate(dev, ifr->ifr_data);
		case EQL_GETSLAVECFG:
			return eql_g_slave_cfg(dev, ifr->ifr_data);
		case EQL_SETSLAVECFG:
			return eql_s_slave_cfg(dev, ifr->ifr_data);
		case EQL_GETMASTRCFG:
			return eql_g_master_cfg(dev, ifr->ifr_data);
		case EQL_SETMASTRCFG:
			return eql_s_master_cfg(dev, ifr->ifr_data);
		default:
			return -EOPNOTSUPP;
	}
}