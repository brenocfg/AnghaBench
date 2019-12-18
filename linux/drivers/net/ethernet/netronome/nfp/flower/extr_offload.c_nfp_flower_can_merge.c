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
typedef  scalar_t__ u8 ;
struct nfp_flower_merge_check {int /*<<< orphan*/  vals; } ;
struct nfp_fl_payload {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ NFP_FL_ACTION_OPCODE_OUTPUT ; 
 int bitmap_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nfp_flower_populate_merge_match (struct nfp_fl_payload*,struct nfp_flower_merge_check*,int) ; 
 int nfp_flower_update_merge_with_actions (struct nfp_fl_payload*,struct nfp_flower_merge_check*,scalar_t__*,int*) ; 

__attribute__((used)) static int
nfp_flower_can_merge(struct nfp_fl_payload *sub_flow1,
		     struct nfp_fl_payload *sub_flow2)
{
	/* Two flows can be merged if sub_flow2 only matches on bits that are
	 * either matched by sub_flow1 or set by a sub_flow1 action. This
	 * ensures that every packet that hits sub_flow1 and recirculates is
	 * guaranteed to hit sub_flow2.
	 */
	struct nfp_flower_merge_check sub_flow1_merge, sub_flow2_merge;
	int err, act_out = 0;
	u8 last_act_id = 0;

	err = nfp_flower_populate_merge_match(sub_flow1, &sub_flow1_merge,
					      true);
	if (err)
		return err;

	err = nfp_flower_populate_merge_match(sub_flow2, &sub_flow2_merge,
					      false);
	if (err)
		return err;

	err = nfp_flower_update_merge_with_actions(sub_flow1, &sub_flow1_merge,
						   &last_act_id, &act_out);
	if (err)
		return err;

	/* Must only be 1 output action and it must be the last in sequence. */
	if (act_out != 1 || last_act_id != NFP_FL_ACTION_OPCODE_OUTPUT)
		return -EOPNOTSUPP;

	/* Reject merge if sub_flow2 matches on something that is not matched
	 * on or set in an action by sub_flow1.
	 */
	err = bitmap_andnot(sub_flow2_merge.vals, sub_flow2_merge.vals,
			    sub_flow1_merge.vals,
			    sizeof(struct nfp_flower_merge_check) * 8);
	if (err)
		return -EINVAL;

	return 0;
}