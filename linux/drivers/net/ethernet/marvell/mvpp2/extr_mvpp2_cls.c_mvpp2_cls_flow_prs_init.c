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
struct TYPE_2__ {int /*<<< orphan*/  ri_mask; int /*<<< orphan*/  ri; } ;
struct mvpp2_cls_flow {TYPE_1__ prs_ri; int /*<<< orphan*/  flow_id; } ;
struct mvpp2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mvpp2_prs_add_flow (struct mvpp2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvpp2_cls_flow_prs_init(struct mvpp2 *priv,
				    const struct mvpp2_cls_flow *flow)
{
	mvpp2_prs_add_flow(priv, flow->flow_id, flow->prs_ri.ri,
			   flow->prs_ri.ri_mask);
}