#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_qla_host {int /*<<< orphan*/  flags; TYPE_3__* reg; } ;
struct TYPE_5__ {int /*<<< orphan*/  intr_mask; } ;
struct TYPE_4__ {TYPE_2__ isp4022; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctrl_status; TYPE_1__ u1; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INTERRUPTS_ON ; 
 int /*<<< orphan*/  CSR_SCSI_INTR_ENABLE ; 
 int /*<<< orphan*/  IMR_SCSI_INTR_ENABLE ; 
 int is_qla4022 (struct scsi_qla_host*) ; 
 int is_qla4032 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_rmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
__qla4xxx_enable_intrs(struct scsi_qla_host *ha)
{
	if (is_qla4022(ha) | is_qla4032(ha)) {
		writel(set_rmask(IMR_SCSI_INTR_ENABLE),
		       &ha->reg->u1.isp4022.intr_mask);
		readl(&ha->reg->u1.isp4022.intr_mask);
	} else {
		writel(set_rmask(CSR_SCSI_INTR_ENABLE), &ha->reg->ctrl_status);
		readl(&ha->reg->ctrl_status);
	}
	set_bit(AF_INTERRUPTS_ON, &ha->flags);
}