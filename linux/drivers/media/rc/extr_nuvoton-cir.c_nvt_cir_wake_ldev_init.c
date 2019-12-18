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
struct nvt_dev {int /*<<< orphan*/  cir_wake_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIR_WAKE_ENABLE_BIT ; 
 int /*<<< orphan*/  CR_ACPI_CIR_WAKE ; 
 int /*<<< orphan*/  CR_ACPI_IRQ_EVENTS2 ; 
 int /*<<< orphan*/  CR_LOGICAL_DEV_EN ; 
 int /*<<< orphan*/  LOGICAL_DEV_ACPI ; 
 int /*<<< orphan*/  LOGICAL_DEV_CIR_WAKE ; 
 int /*<<< orphan*/  LOGICAL_DEV_ENABLE ; 
 int /*<<< orphan*/  PME_INTR_CIR_PASS_BIT ; 
 int /*<<< orphan*/  nvt_cr_write (struct nvt_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvt_dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvt_select_logical_dev (struct nvt_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvt_set_ioaddr (struct nvt_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvt_set_reg_bit (struct nvt_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvt_cir_wake_ldev_init(struct nvt_dev *nvt)
{
	/* Select ACPI logical device and anable it */
	nvt_select_logical_dev(nvt, LOGICAL_DEV_ACPI);
	nvt_cr_write(nvt, LOGICAL_DEV_ENABLE, CR_LOGICAL_DEV_EN);

	/* Enable CIR Wake via PSOUT# (Pin60) */
	nvt_set_reg_bit(nvt, CIR_WAKE_ENABLE_BIT, CR_ACPI_CIR_WAKE);

	/* enable pme interrupt of cir wakeup event */
	nvt_set_reg_bit(nvt, PME_INTR_CIR_PASS_BIT, CR_ACPI_IRQ_EVENTS2);

	/* Select CIR Wake logical device */
	nvt_select_logical_dev(nvt, LOGICAL_DEV_CIR_WAKE);

	nvt_set_ioaddr(nvt, &nvt->cir_wake_addr);

	nvt_dbg("CIR Wake initialized, base io port address: 0x%lx",
		nvt->cir_wake_addr);
}