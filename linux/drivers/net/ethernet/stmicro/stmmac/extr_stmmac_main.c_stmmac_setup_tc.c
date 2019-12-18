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
struct stmmac_priv {int dummy; } ;
struct net_device {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_BLOCK 129 
#define  TC_SETUP_QDISC_CBS 128 
 int flow_block_cb_setup_simple (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct stmmac_priv*,struct stmmac_priv*,int) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stmmac_block_cb_list ; 
 int /*<<< orphan*/  stmmac_setup_tc_block_cb ; 
 int stmmac_tc_setup_cbs (struct stmmac_priv*,struct stmmac_priv*,void*) ; 

__attribute__((used)) static int stmmac_setup_tc(struct net_device *ndev, enum tc_setup_type type,
			   void *type_data)
{
	struct stmmac_priv *priv = netdev_priv(ndev);

	switch (type) {
	case TC_SETUP_BLOCK:
		return flow_block_cb_setup_simple(type_data,
						  &stmmac_block_cb_list,
						  stmmac_setup_tc_block_cb,
						  priv, priv, true);
	case TC_SETUP_QDISC_CBS:
		return stmmac_tc_setup_cbs(priv, priv, type_data);
	default:
		return -EOPNOTSUPP;
	}
}