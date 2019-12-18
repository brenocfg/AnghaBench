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
struct qed_hwfn {int dummy; } ;
typedef  enum protocol_type { ____Placeholder_protocol_type } protocol_type ;

/* Variables and functions */
 int /*<<< orphan*/  QED_CXT_PF_CID ; 
 int _qed_cxt_acquire_cid (struct qed_hwfn*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int qed_cxt_acquire_cid(struct qed_hwfn *p_hwfn,
			enum protocol_type type, u32 *p_cid)
{
	return _qed_cxt_acquire_cid(p_hwfn, type, p_cid, QED_CXT_PF_CID);
}