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
struct bnxt_tc_info {int /*<<< orphan*/  encap_table; int /*<<< orphan*/  decap_table; int /*<<< orphan*/  decap_l2_table; int /*<<< orphan*/  l2_table; int /*<<< orphan*/  flow_table; } ;
struct bnxt {struct bnxt_tc_info* tc_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_tc_flower_enabled (struct bnxt*) ; 
 int /*<<< orphan*/  kfree (struct bnxt_tc_info*) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 

void bnxt_shutdown_tc(struct bnxt *bp)
{
	struct bnxt_tc_info *tc_info = bp->tc_info;

	if (!bnxt_tc_flower_enabled(bp))
		return;

	rhashtable_destroy(&tc_info->flow_table);
	rhashtable_destroy(&tc_info->l2_table);
	rhashtable_destroy(&tc_info->decap_l2_table);
	rhashtable_destroy(&tc_info->decap_table);
	rhashtable_destroy(&tc_info->encap_table);
	kfree(tc_info);
	bp->tc_info = NULL;
}