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
struct tg3 {int /*<<< orphan*/  misc_host_ctrl; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TG3PCI_MISC_HOST_CTRL ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_enable_register_access(struct tg3 *tp)
{
	/*
	 * Make sure register accesses (indirect or otherwise) will function
	 * correctly.
	 */
	pci_write_config_dword(tp->pdev,
			       TG3PCI_MISC_HOST_CTRL, tp->misc_host_ctrl);
}