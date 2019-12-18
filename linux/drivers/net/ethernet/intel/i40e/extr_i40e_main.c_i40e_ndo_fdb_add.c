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
typedef  int u16 ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct ndmsg {int ndm_state; } ;
struct i40e_pf {int flags; } ;
struct i40e_netdev_priv {TYPE_1__* vsi; } ;
struct TYPE_2__ {struct i40e_pf* back; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int I40E_FLAG_SRIOV_ENABLED ; 
 int NLM_F_EXCL ; 
 int NUD_PERMANENT ; 
 int dev_mc_add_excl (struct net_device*,unsigned char const*) ; 
 int dev_uc_add_excl (struct net_device*,unsigned char const*) ; 
 scalar_t__ is_link_local_ether_addr (unsigned char const*) ; 
 scalar_t__ is_multicast_ether_addr (unsigned char const*) ; 
 scalar_t__ is_unicast_ether_addr (unsigned char const*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_ndo_fdb_add(struct ndmsg *ndm, struct nlattr *tb[],
			    struct net_device *dev,
			    const unsigned char *addr, u16 vid,
			    u16 flags,
			    struct netlink_ext_ack *extack)
{
	struct i40e_netdev_priv *np = netdev_priv(dev);
	struct i40e_pf *pf = np->vsi->back;
	int err = 0;

	if (!(pf->flags & I40E_FLAG_SRIOV_ENABLED))
		return -EOPNOTSUPP;

	if (vid) {
		pr_info("%s: vlans aren't supported yet for dev_uc|mc_add()\n", dev->name);
		return -EINVAL;
	}

	/* Hardware does not support aging addresses so if a
	 * ndm_state is given only allow permanent addresses
	 */
	if (ndm->ndm_state && !(ndm->ndm_state & NUD_PERMANENT)) {
		netdev_info(dev, "FDB only supports static addresses\n");
		return -EINVAL;
	}

	if (is_unicast_ether_addr(addr) || is_link_local_ether_addr(addr))
		err = dev_uc_add_excl(dev, addr);
	else if (is_multicast_ether_addr(addr))
		err = dev_mc_add_excl(dev, addr);
	else
		err = -EINVAL;

	/* Only return duplicate errors if NLM_F_EXCL is set */
	if (err == -EEXIST && !(flags & NLM_F_EXCL))
		err = 0;

	return err;
}