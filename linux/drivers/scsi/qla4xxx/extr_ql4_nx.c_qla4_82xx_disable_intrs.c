#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tgt_mask_reg; } ;
struct scsi_qla_host {int /*<<< orphan*/  hardware_lock; TYPE_1__ nx_legacy_intr; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INTERRUPTS_ON ; 
 int /*<<< orphan*/  qla4_82xx_wr_32 (struct scsi_qla_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qla4_8xxx_intr_disable (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
qla4_82xx_disable_intrs(struct scsi_qla_host *ha)
{
	if (test_and_clear_bit(AF_INTERRUPTS_ON, &ha->flags))
		qla4_8xxx_intr_disable(ha);

	spin_lock_irq(&ha->hardware_lock);
	/* BIT 10 - set */
	qla4_82xx_wr_32(ha, ha->nx_legacy_intr.tgt_mask_reg, 0x0400);
	spin_unlock_irq(&ha->hardware_lock);
}