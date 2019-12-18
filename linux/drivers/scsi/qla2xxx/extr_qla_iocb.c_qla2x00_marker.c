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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct scsi_qla_host {int dummy; } ;
struct qla_qpair {int /*<<< orphan*/  qp_lock_ptr; } ;

/* Variables and functions */
 int __qla2x00_marker (struct scsi_qla_host*,struct qla_qpair*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

int
qla2x00_marker(struct scsi_qla_host *vha, struct qla_qpair *qpair,
    uint16_t loop_id, uint64_t lun, uint8_t type)
{
	int ret;
	unsigned long flags = 0;

	spin_lock_irqsave(qpair->qp_lock_ptr, flags);
	ret = __qla2x00_marker(vha, qpair, loop_id, lun, type);
	spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);

	return (ret);
}