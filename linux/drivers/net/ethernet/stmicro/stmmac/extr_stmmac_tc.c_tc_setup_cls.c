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
struct flow_cls_offload {int command; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  FLOW_CLS_DESTROY 129 
#define  FLOW_CLS_REPLACE 128 
 int tc_add_flow (struct stmmac_priv*,struct flow_cls_offload*) ; 
 int tc_del_flow (struct stmmac_priv*,struct flow_cls_offload*) ; 

__attribute__((used)) static int tc_setup_cls(struct stmmac_priv *priv,
			struct flow_cls_offload *cls)
{
	int ret = 0;

	switch (cls->command) {
	case FLOW_CLS_REPLACE:
		ret = tc_add_flow(priv, cls);
		break;
	case FLOW_CLS_DESTROY:
		ret = tc_del_flow(priv, cls);
		break;
	default:
		return -EOPNOTSUPP;
	}

	return ret;
}