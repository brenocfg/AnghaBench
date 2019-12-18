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
struct ehci_hcd {TYPE_1__* regs; scalar_t__ frame_index_bug; } ;
struct TYPE_2__ {int /*<<< orphan*/  frame_index; } ;

/* Variables and functions */
 int ehci_moschip_read_frame_index (struct ehci_hcd*) ; 
 int ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned ehci_read_frame_index(struct ehci_hcd *ehci)
{
	if (ehci->frame_index_bug)
		return ehci_moschip_read_frame_index(ehci);
	return ehci_readl(ehci, &ehci->regs->frame_index);
}