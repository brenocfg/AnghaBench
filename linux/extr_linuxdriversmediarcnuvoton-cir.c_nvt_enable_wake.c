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
struct nvt_dev {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIR_WAKE_ENABLE_BIT ; 
 int /*<<< orphan*/  CIR_WAKE_IRCON ; 
 int CIR_WAKE_IRCON_MODE0 ; 
 int CIR_WAKE_IRCON_R ; 
 int CIR_WAKE_IRCON_RXEN ; 
 int CIR_WAKE_IRCON_RXINV ; 
 int CIR_WAKE_IRCON_SAMPLE_PERIOD_SEL ; 
 int /*<<< orphan*/  CIR_WAKE_IREN ; 
 int /*<<< orphan*/  CIR_WAKE_IRSTS ; 
 int /*<<< orphan*/  CR_ACPI_CIR_WAKE ; 
 int /*<<< orphan*/  CR_ACPI_IRQ_EVENTS2 ; 
 int /*<<< orphan*/  CR_LOGICAL_DEV_EN ; 
 int /*<<< orphan*/  LOGICAL_DEV_ACPI ; 
 int /*<<< orphan*/  LOGICAL_DEV_CIR_WAKE ; 
 int /*<<< orphan*/  LOGICAL_DEV_ENABLE ; 
 int /*<<< orphan*/  PME_INTR_CIR_PASS_BIT ; 
 int /*<<< orphan*/  nvt_cir_wake_reg_write (struct nvt_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvt_cr_write (struct nvt_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvt_efm_disable (struct nvt_dev*) ; 
 int /*<<< orphan*/  nvt_efm_enable (struct nvt_dev*) ; 
 int /*<<< orphan*/  nvt_select_logical_dev (struct nvt_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvt_set_reg_bit (struct nvt_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void nvt_enable_wake(struct nvt_dev *nvt)
{
	unsigned long flags;

	nvt_efm_enable(nvt);

	nvt_select_logical_dev(nvt, LOGICAL_DEV_ACPI);
	nvt_set_reg_bit(nvt, CIR_WAKE_ENABLE_BIT, CR_ACPI_CIR_WAKE);
	nvt_set_reg_bit(nvt, PME_INTR_CIR_PASS_BIT, CR_ACPI_IRQ_EVENTS2);

	nvt_select_logical_dev(nvt, LOGICAL_DEV_CIR_WAKE);
	nvt_cr_write(nvt, LOGICAL_DEV_ENABLE, CR_LOGICAL_DEV_EN);

	nvt_efm_disable(nvt);

	spin_lock_irqsave(&nvt->lock, flags);

	nvt_cir_wake_reg_write(nvt, CIR_WAKE_IRCON_MODE0 | CIR_WAKE_IRCON_RXEN |
			       CIR_WAKE_IRCON_R | CIR_WAKE_IRCON_RXINV |
			       CIR_WAKE_IRCON_SAMPLE_PERIOD_SEL,
			       CIR_WAKE_IRCON);
	nvt_cir_wake_reg_write(nvt, 0xff, CIR_WAKE_IRSTS);
	nvt_cir_wake_reg_write(nvt, 0, CIR_WAKE_IREN);

	spin_unlock_irqrestore(&nvt->lock, flags);
}