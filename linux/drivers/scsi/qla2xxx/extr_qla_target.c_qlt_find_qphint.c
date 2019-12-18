#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {scalar_t__ qpairs_available; } ;
struct TYPE_3__ {struct qla_tgt* qla_tgt; } ;
struct scsi_qla_host {TYPE_2__ flags; TYPE_1__ vha_tgt; } ;
struct qla_tgt {struct qla_qpair_hint* qphints; int /*<<< orphan*/  lun_qpair_map; } ;
struct qla_qpair_hint {int dummy; } ;

/* Variables and functions */
 struct qla_qpair_hint* btree_lookup64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct qla_qpair_hint *qlt_find_qphint(struct scsi_qla_host *vha,
    uint64_t unpacked_lun)
{
	struct qla_tgt *tgt = vha->vha_tgt.qla_tgt;
	struct qla_qpair_hint *h = NULL;

	if (vha->flags.qpairs_available) {
		h = btree_lookup64(&tgt->lun_qpair_map, unpacked_lun);
		if (!h)
			h = &tgt->qphints[0];
	} else {
		h = &tgt->qphints[0];
	}

	return h;
}