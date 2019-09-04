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
 int /*<<< orphan*/  pci_cleanup_aer_uncorrect_error_status (struct pci_dev*) ; 

__attribute__((used)) static void netxen_io_resume(struct pci_dev *pdev)
{
	pci_cleanup_aer_uncorrect_error_status(pdev);
}