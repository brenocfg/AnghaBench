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
 int /*<<< orphan*/  QEDE_REMOVE_NORMAL ; 
 int /*<<< orphan*/  __qede_remove (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qede_shutdown(struct pci_dev *pdev)
{
	__qede_remove(pdev, QEDE_REMOVE_NORMAL);
}