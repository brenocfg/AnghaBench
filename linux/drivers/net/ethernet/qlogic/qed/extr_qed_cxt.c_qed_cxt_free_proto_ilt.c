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
 int PROTOCOLID_ROCE ; 
 int /*<<< orphan*/  QED_ELEM_CXT ; 
 int /*<<< orphan*/  QED_ELEM_SRQ ; 
 int /*<<< orphan*/  QED_ELEM_TASK ; 
 int qed_cxt_free_ilt_range (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_cxt_get_proto_cid_count (struct qed_hwfn*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_cxt_get_proto_cid_start (struct qed_hwfn*,int) ; 
 int /*<<< orphan*/  qed_cxt_get_proto_tid_count (struct qed_hwfn*,int) ; 
 int /*<<< orphan*/  qed_cxt_get_srq_count (struct qed_hwfn*) ; 

int qed_cxt_free_proto_ilt(struct qed_hwfn *p_hwfn, enum protocol_type proto)
{
	int rc;
	u32 cid;

	/* Free Connection CXT */
	rc = qed_cxt_free_ilt_range(p_hwfn, QED_ELEM_CXT,
				    qed_cxt_get_proto_cid_start(p_hwfn,
								proto),
				    qed_cxt_get_proto_cid_count(p_hwfn,
								proto, &cid));

	if (rc)
		return rc;

	/* Free Task CXT ( Intentionally RoCE as task-id is shared between
	 * RoCE and iWARP )
	 */
	proto = PROTOCOLID_ROCE;
	rc = qed_cxt_free_ilt_range(p_hwfn, QED_ELEM_TASK, 0,
				    qed_cxt_get_proto_tid_count(p_hwfn, proto));
	if (rc)
		return rc;

	/* Free TSDM CXT */
	rc = qed_cxt_free_ilt_range(p_hwfn, QED_ELEM_SRQ, 0,
				    qed_cxt_get_srq_count(p_hwfn));

	return rc;
}