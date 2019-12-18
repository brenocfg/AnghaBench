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
struct de_private {int /*<<< orphan*/  pdev; scalar_t__ de21040; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIPM ; 
 int PM_Mask ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void de_adapter_wake (struct de_private *de)
{
	u32 pmctl;

	if (de->de21040)
		return;

	pci_read_config_dword(de->pdev, PCIPM, &pmctl);
	if (pmctl & PM_Mask) {
		pmctl &= ~PM_Mask;
		pci_write_config_dword(de->pdev, PCIPM, pmctl);

		/* de4x5.c delays, so we do too */
		msleep(10);
	}
}