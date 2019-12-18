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
 int /*<<< orphan*/  NI_AI_ConvertClock ; 
 int /*<<< orphan*/  NI_AI_SampleClock ; 
 int /*<<< orphan*/  NI_AI_StartTrigger ; 
 int /*<<< orphan*/  NI_AO_SampleClock ; 
 int /*<<< orphan*/  NI_AO_SampleClockTimebase ; 
 int /*<<< orphan*/  NI_DO_SampleClock ; 
 int /*<<< orphan*/  init_pci_fake () ; 
 int ni_is_cmd_dest (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unittest (int,char*) ; 

void test_ni_is_cmd_dest(void)
{
	init_pci_fake();
	unittest(ni_is_cmd_dest(NI_AI_SampleClock),
		 "check that AI/SampleClock is cmd destination\n");
	unittest(ni_is_cmd_dest(NI_AI_StartTrigger),
		 "check that AI/StartTrigger is cmd destination\n");
	unittest(ni_is_cmd_dest(NI_AI_ConvertClock),
		 "check that AI/ConvertClock is cmd destination\n");
	unittest(ni_is_cmd_dest(NI_AO_SampleClock),
		 "check that AO/SampleClock is cmd destination\n");
	unittest(ni_is_cmd_dest(NI_DO_SampleClock),
		 "check that DO/SampleClock is cmd destination\n");
	unittest(!ni_is_cmd_dest(NI_AO_SampleClockTimebase),
		 "check that AO/SampleClockTimebase _not_ cmd destination\n");
}