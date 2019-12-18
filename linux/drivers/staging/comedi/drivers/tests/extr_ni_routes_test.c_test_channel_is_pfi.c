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

/* Variables and functions */
 scalar_t__ NI_PFI (int) ; 
 int channel_is_pfi (scalar_t__) ; 
 int /*<<< orphan*/  init_pci_fake () ; 
 int /*<<< orphan*/  unittest (int,char*) ; 

void test_channel_is_pfi(void)
{
	init_pci_fake();
	unittest(channel_is_pfi(NI_PFI(0)), "check First pfi channel\n");
	unittest(channel_is_pfi(NI_PFI(10)), "check 10th pfi channel\n");
	unittest(channel_is_pfi(NI_PFI(-1)), "check last pfi channel\n");
	unittest(!channel_is_pfi(NI_PFI(-1) + 1),
		 "check first non pfi channel\n");
}