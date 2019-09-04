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
struct nfp_repr {int /*<<< orphan*/  netdev; int /*<<< orphan*/  app; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_CLSFLOWER 128 
 int nfp_flower_repr_offload (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  tc_cls_can_offload_and_chain0 (int /*<<< orphan*/ ,void*) ; 

int nfp_flower_setup_tc_egress_cb(enum tc_setup_type type, void *type_data,
				  void *cb_priv)
{
	struct nfp_repr *repr = cb_priv;

	if (!tc_cls_can_offload_and_chain0(repr->netdev, type_data))
		return -EOPNOTSUPP;

	switch (type) {
	case TC_SETUP_CLSFLOWER:
		return nfp_flower_repr_offload(repr->app, repr->netdev,
					       type_data, true);
	default:
		return -EOPNOTSUPP;
	}
}