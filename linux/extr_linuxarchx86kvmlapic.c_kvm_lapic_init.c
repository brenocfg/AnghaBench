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
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  apic_hw_disabled ; 
 int /*<<< orphan*/  apic_sw_disabled ; 
 int /*<<< orphan*/  jump_label_rate_limit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void kvm_lapic_init(void)
{
	/* do not patch jump label more than once per second */
	jump_label_rate_limit(&apic_hw_disabled, HZ);
	jump_label_rate_limit(&apic_sw_disabled, HZ);
}