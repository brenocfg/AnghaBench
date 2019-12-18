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
struct stmmac_priv {int /*<<< orphan*/  dev; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_CLSFLOWER 129 
#define  TC_SETUP_CLSU32 128 
 int /*<<< orphan*/  stmmac_disable_all_queues (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_enable_all_queues (struct stmmac_priv*) ; 
 int stmmac_tc_setup_cls (struct stmmac_priv*,struct stmmac_priv*,void*) ; 
 int stmmac_tc_setup_cls_u32 (struct stmmac_priv*,struct stmmac_priv*,void*) ; 
 int /*<<< orphan*/  tc_cls_can_offload_and_chain0 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int stmmac_setup_tc_block_cb(enum tc_setup_type type, void *type_data,
				    void *cb_priv)
{
	struct stmmac_priv *priv = cb_priv;
	int ret = -EOPNOTSUPP;

	if (!tc_cls_can_offload_and_chain0(priv->dev, type_data))
		return ret;

	stmmac_disable_all_queues(priv);

	switch (type) {
	case TC_SETUP_CLSU32:
		ret = stmmac_tc_setup_cls_u32(priv, priv, type_data);
		break;
	case TC_SETUP_CLSFLOWER:
		ret = stmmac_tc_setup_cls(priv, priv, type_data);
		break;
	default:
		break;
	}

	stmmac_enable_all_queues(priv);
	return ret;
}