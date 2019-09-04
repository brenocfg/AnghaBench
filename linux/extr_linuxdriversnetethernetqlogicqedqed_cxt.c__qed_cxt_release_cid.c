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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct qed_hwfn {int dummy; } ;
struct qed_cid_acquired_map {int /*<<< orphan*/  cid_map; scalar_t__ start_cid; } ;
typedef  enum protocol_type { ____Placeholder_protocol_type } protocol_type ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAX_NUM_VFS ; 
 int /*<<< orphan*/  QED_CXT_PF_CID ; 
 int /*<<< orphan*/  QED_MSG_CXT ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int qed_cxt_test_cid_acquired (struct qed_hwfn*,scalar_t__,int /*<<< orphan*/ ,int*,struct qed_cid_acquired_map**) ; 

void _qed_cxt_release_cid(struct qed_hwfn *p_hwfn, u32 cid, u8 vfid)
{
	struct qed_cid_acquired_map *p_map = NULL;
	enum protocol_type type;
	bool b_acquired;
	u32 rel_cid;

	if (vfid != QED_CXT_PF_CID && vfid > MAX_NUM_VFS) {
		DP_NOTICE(p_hwfn,
			  "Trying to return incorrect CID belonging to VF %02x\n",
			  vfid);
		return;
	}

	/* Test acquired and find matching per-protocol map */
	b_acquired = qed_cxt_test_cid_acquired(p_hwfn, cid, vfid,
					       &type, &p_map);

	if (!b_acquired)
		return;

	rel_cid = cid - p_map->start_cid;
	clear_bit(rel_cid, p_map->cid_map);

	DP_VERBOSE(p_hwfn, QED_MSG_CXT,
		   "Released CID 0x%08x [rel. %08x] vfid %02x type %d\n",
		   cid, rel_cid, vfid, type);
}