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
struct idt_89hpesx_dev {int eero; scalar_t__ eeaddr; scalar_t__ inieecmd; scalar_t__ eesize; } ;

/* Variables and functions */

__attribute__((used)) static void idt_set_defval(struct idt_89hpesx_dev *pdev)
{
	/* If OF info is missing then use next values */
	pdev->eesize = 0;
	pdev->eero = true;
	pdev->inieecmd = 0;
	pdev->eeaddr = 0;
}