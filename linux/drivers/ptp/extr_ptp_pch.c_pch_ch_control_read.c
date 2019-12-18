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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;
struct pch_dev {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ch_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ *) ; 
 struct pch_dev* pci_get_drvdata (struct pci_dev*) ; 

u32 pch_ch_control_read(struct pci_dev *pdev)
{
	struct pch_dev *chip = pci_get_drvdata(pdev);
	u32 val;

	val = ioread32(&chip->regs->ch_control);

	return val;
}