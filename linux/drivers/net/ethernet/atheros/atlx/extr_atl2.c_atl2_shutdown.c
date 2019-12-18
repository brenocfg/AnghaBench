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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMSG_SUSPEND ; 
 int /*<<< orphan*/  atl2_suspend (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atl2_shutdown(struct pci_dev *pdev)
{
	atl2_suspend(pdev, PMSG_SUSPEND);
}