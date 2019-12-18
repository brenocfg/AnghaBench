#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct TYPE_6__ {int /*<<< orphan*/  protocol_id; int /*<<< orphan*/  cmd_id; int /*<<< orphan*/  cid; } ;
struct TYPE_8__ {TYPE_3__ data_ptr; TYPE_2__ hdr; } ;
struct TYPE_5__ {int /*<<< orphan*/  function; } ;
struct qed_spq_entry {int comp_mode; TYPE_4__ elem; TYPE_1__ comp_cb; scalar_t__ flags; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_TRINE (int,int const,int const,char*,char*,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  QED_MSG_SPQ ; 
#define  QED_SPQ_MODE_BLOCK 130 
#define  QED_SPQ_MODE_CB 129 
#define  QED_SPQ_MODE_EBLOCK 128 
 int /*<<< orphan*/  qed_spq_blocking_cb ; 

__attribute__((used)) static int qed_spq_fill_entry(struct qed_hwfn *p_hwfn,
			      struct qed_spq_entry *p_ent)
{
	p_ent->flags = 0;

	switch (p_ent->comp_mode) {
	case QED_SPQ_MODE_EBLOCK:
	case QED_SPQ_MODE_BLOCK:
		p_ent->comp_cb.function = qed_spq_blocking_cb;
		break;
	case QED_SPQ_MODE_CB:
		break;
	default:
		DP_NOTICE(p_hwfn, "Unknown SPQE completion mode %d\n",
			  p_ent->comp_mode);
		return -EINVAL;
	}

	DP_VERBOSE(p_hwfn, QED_MSG_SPQ,
		   "Ramrod header: [CID 0x%08x CMD 0x%02x protocol 0x%02x] Data pointer: [%08x:%08x] Completion Mode: %s\n",
		   p_ent->elem.hdr.cid,
		   p_ent->elem.hdr.cmd_id,
		   p_ent->elem.hdr.protocol_id,
		   p_ent->elem.data_ptr.hi,
		   p_ent->elem.data_ptr.lo,
		   D_TRINE(p_ent->comp_mode, QED_SPQ_MODE_EBLOCK,
			   QED_SPQ_MODE_BLOCK, "MODE_EBLOCK", "MODE_BLOCK",
			   "MODE_CB"));

	return 0;
}