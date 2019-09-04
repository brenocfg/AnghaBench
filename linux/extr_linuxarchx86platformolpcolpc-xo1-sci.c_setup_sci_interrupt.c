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
typedef  int u32 ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS5536_PIC_INT_SEL1 ; 
 int /*<<< orphan*/  CS5536_PIC_INT_SEL2 ; 
 scalar_t__ CS5536_PM1_STS ; 
 int CS5536_PM_PWRBTN ; 
 int CS5536_PM_RTC ; 
 int /*<<< orphan*/  DRV_NAME ; 
 scalar_t__ acpi_base ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  rdmsr (int,int,int) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct platform_device*) ; 
 int sci_irq ; 
 int /*<<< orphan*/  wrmsrl (int,int) ; 
 int /*<<< orphan*/  xo1_sci_intr ; 

__attribute__((used)) static int setup_sci_interrupt(struct platform_device *pdev)
{
	u32 lo, hi;
	u32 sts;
	int r;

	rdmsr(0x51400020, lo, hi);
	sci_irq = (lo >> 20) & 15;

	if (sci_irq) {
		dev_info(&pdev->dev, "SCI is mapped to IRQ %d\n", sci_irq);
	} else {
		/* Zero means masked */
		dev_info(&pdev->dev, "SCI unmapped. Mapping to IRQ 3\n");
		sci_irq = 3;
		lo |= 0x00300000;
		wrmsrl(0x51400020, lo);
	}

	/* Select level triggered in PIC */
	if (sci_irq < 8) {
		lo = inb(CS5536_PIC_INT_SEL1);
		lo |= 1 << sci_irq;
		outb(lo, CS5536_PIC_INT_SEL1);
	} else {
		lo = inb(CS5536_PIC_INT_SEL2);
		lo |= 1 << (sci_irq - 8);
		outb(lo, CS5536_PIC_INT_SEL2);
	}

	/* Enable interesting SCI events, and clear pending interrupts */
	sts = inl(acpi_base + CS5536_PM1_STS);
	outl(((CS5536_PM_PWRBTN | CS5536_PM_RTC) << 16) | 0xffff,
	     acpi_base + CS5536_PM1_STS);

	r = request_irq(sci_irq, xo1_sci_intr, 0, DRV_NAME, pdev);
	if (r)
		dev_err(&pdev->dev, "can't request interrupt\n");

	return r;
}