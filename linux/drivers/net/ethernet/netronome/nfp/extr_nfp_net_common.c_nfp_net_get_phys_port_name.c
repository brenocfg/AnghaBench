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
struct TYPE_2__ {scalar_t__ is_vf; } ;
struct nfp_net {int id; scalar_t__ vnic_no_name; TYPE_1__ dp; scalar_t__ port; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 struct nfp_net* netdev_priv (struct net_device*) ; 
 int snprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static int
nfp_net_get_phys_port_name(struct net_device *netdev, char *name, size_t len)
{
	struct nfp_net *nn = netdev_priv(netdev);
	int n;

	/* If port is defined, devlink_port is registered and devlink core
	 * is taking care of name formatting.
	 */
	if (nn->port)
		return -EOPNOTSUPP;

	if (nn->dp.is_vf || nn->vnic_no_name)
		return -EOPNOTSUPP;

	n = snprintf(name, len, "n%d", nn->id);
	if (n >= len)
		return -EINVAL;

	return 0;
}