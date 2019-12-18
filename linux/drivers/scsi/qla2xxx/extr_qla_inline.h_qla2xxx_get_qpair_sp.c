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
typedef  int /*<<< orphan*/  uint8_t ;
struct qla_qpair {int /*<<< orphan*/  srb_mempool; } ;
typedef  int /*<<< orphan*/  srb_t ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  fc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA_QPAIR_MARK_BUSY (struct qla_qpair*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLA_QPAIR_MARK_NOT_BUSY (struct qla_qpair*) ; 
 int /*<<< orphan*/ * mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2xxx_init_sp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct qla_qpair*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline srb_t *
qla2xxx_get_qpair_sp(scsi_qla_host_t *vha, struct qla_qpair *qpair,
    fc_port_t *fcport, gfp_t flag)
{
	srb_t *sp = NULL;
	uint8_t bail;

	QLA_QPAIR_MARK_BUSY(qpair, bail);
	if (unlikely(bail))
		return NULL;

	sp = mempool_alloc(qpair->srb_mempool, flag);
	if (sp)
		qla2xxx_init_sp(sp, vha, qpair, fcport);
	else
		QLA_QPAIR_MARK_NOT_BUSY(qpair);
	return sp;
}