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
struct mvpp2_cls_lookup_entry {int /*<<< orphan*/  data; int /*<<< orphan*/  lkpid; scalar_t__ way; } ;
struct mvpp2_cls_flow {int /*<<< orphan*/  flow_id; } ;
struct mvpp2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_CLS_FLT_FIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVPP2_CLS_LKP_FLOW_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVPP2_CLS_LKP_TBL_LOOKUP_EN_MASK ; 
 int /*<<< orphan*/  mvpp2_cls_lookup_write (struct mvpp2*,struct mvpp2_cls_lookup_entry*) ; 

__attribute__((used)) static void mvpp2_cls_flow_lkp_init(struct mvpp2 *priv,
				    const struct mvpp2_cls_flow *flow)
{
	struct mvpp2_cls_lookup_entry le;

	le.way = 0;
	le.lkpid = flow->flow_id;

	/* The default RxQ for this port is set in the C2 lookup */
	le.data = 0;

	/* We point on the first lookup in the sequence for the flow, that is
	 * the C2 lookup.
	 */
	le.data |= MVPP2_CLS_LKP_FLOW_PTR(MVPP2_CLS_FLT_FIRST(flow->flow_id));

	/* CLS is always enabled, RSS is enabled/disabled in C2 lookup */
	le.data |= MVPP2_CLS_LKP_TBL_LOOKUP_EN_MASK;

	mvpp2_cls_lookup_write(priv, &le);
}