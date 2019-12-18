#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct qla_qpair {int dummy; } ;
struct TYPE_11__ {TYPE_3__* vha; } ;
typedef  TYPE_2__ srb_t ;
struct TYPE_12__ {TYPE_1__* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  fc_port_t ;
struct TYPE_10__ {struct qla_qpair* base_qpair; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLA_VHA_MARK_BUSY (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLA_VHA_MARK_NOT_BUSY (TYPE_3__*) ; 
 TYPE_2__* qla2xxx_get_qpair_sp (TYPE_3__*,struct qla_qpair*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline srb_t *
qla2x00_get_sp(scsi_qla_host_t *vha, fc_port_t *fcport, gfp_t flag)
{
	srb_t *sp = NULL;
	uint8_t bail;
	struct qla_qpair *qpair;

	QLA_VHA_MARK_BUSY(vha, bail);
	if (unlikely(bail))
		return NULL;

	qpair = vha->hw->base_qpair;
	sp = qla2xxx_get_qpair_sp(vha, qpair, fcport, flag);
	if (!sp)
		goto done;

	sp->vha = vha;
done:
	if (!sp)
		QLA_VHA_MARK_NOT_BUSY(vha);
	return sp;
}