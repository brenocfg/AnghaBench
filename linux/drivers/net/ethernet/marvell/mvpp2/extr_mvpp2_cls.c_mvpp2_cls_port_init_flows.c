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
struct mvpp2_cls_flow {int dummy; } ;
struct mvpp2 {int dummy; } ;

/* Variables and functions */
 int MVPP2_N_PRS_FLOWS ; 
 struct mvpp2_cls_flow* mvpp2_cls_flow_get (int) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_init (struct mvpp2*,struct mvpp2_cls_flow const*) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_lkp_init (struct mvpp2*,struct mvpp2_cls_flow const*) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_prs_init (struct mvpp2*,struct mvpp2_cls_flow const*) ; 

__attribute__((used)) static void mvpp2_cls_port_init_flows(struct mvpp2 *priv)
{
	const struct mvpp2_cls_flow *flow;
	int i;

	for (i = 0; i < MVPP2_N_PRS_FLOWS; i++) {
		flow = mvpp2_cls_flow_get(i);
		if (!flow)
			break;

		mvpp2_cls_flow_prs_init(priv, flow);
		mvpp2_cls_flow_lkp_init(priv, flow);
		mvpp2_cls_flow_init(priv, flow);
	}
}