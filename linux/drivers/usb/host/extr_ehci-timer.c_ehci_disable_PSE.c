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
struct ehci_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_PSE ; 
 int /*<<< orphan*/  ehci_clear_command_bit (struct ehci_hcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ehci_disable_PSE(struct ehci_hcd *ehci)
{
	ehci_clear_command_bit(ehci, CMD_PSE);
}