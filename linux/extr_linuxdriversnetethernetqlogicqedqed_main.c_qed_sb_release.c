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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct qed_sb_info {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct qed_dev {int num_hwfns; struct qed_hwfn* hwfns; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  NETIF_MSG_INTR ; 
 int /*<<< orphan*/  qed_int_sb_release (struct qed_hwfn*,struct qed_sb_info*,int) ; 

__attribute__((used)) static u32 qed_sb_release(struct qed_dev *cdev,
			  struct qed_sb_info *sb_info, u16 sb_id)
{
	struct qed_hwfn *p_hwfn;
	int hwfn_index;
	u16 rel_sb_id;
	u32 rc;

	hwfn_index = sb_id % cdev->num_hwfns;
	p_hwfn = &cdev->hwfns[hwfn_index];
	rel_sb_id = sb_id / cdev->num_hwfns;

	DP_VERBOSE(cdev, NETIF_MSG_INTR,
		   "hwfn [%d] <--[init]-- SB %04x [0x%04x upper]\n",
		   hwfn_index, rel_sb_id, sb_id);

	rc = qed_int_sb_release(p_hwfn, sb_info, rel_sb_id);

	return rc;
}