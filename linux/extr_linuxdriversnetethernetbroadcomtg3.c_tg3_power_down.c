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
struct tg3 {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  WOL_ENABLE ; 
 int /*<<< orphan*/  pci_set_power_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_wake_from_d3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_power_down(struct tg3 *tp)
{
	pci_wake_from_d3(tp->pdev, tg3_flag(tp, WOL_ENABLE));
	pci_set_power_state(tp->pdev, PCI_D3hot);
}