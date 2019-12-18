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
struct nfp_flower_indr_block_cb_priv {int /*<<< orphan*/  netdev; int /*<<< orphan*/  app; } ;
struct TYPE_2__ {scalar_t__ chain_index; } ;
struct flow_cls_offload {TYPE_1__ common; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_CLSFLOWER 128 
 int nfp_flower_repr_offload (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int nfp_flower_setup_indr_block_cb(enum tc_setup_type type,
					  void *type_data, void *cb_priv)
{
	struct nfp_flower_indr_block_cb_priv *priv = cb_priv;
	struct flow_cls_offload *flower = type_data;

	if (flower->common.chain_index)
		return -EOPNOTSUPP;

	switch (type) {
	case TC_SETUP_CLSFLOWER:
		return nfp_flower_repr_offload(priv->app, priv->netdev,
					       type_data);
	default:
		return -EOPNOTSUPP;
	}
}