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
 int /*<<< orphan*/  apic_hw_disabled ; 
 int /*<<< orphan*/  apic_sw_disabled ; 
 int /*<<< orphan*/  static_key_deferred_flush (int /*<<< orphan*/ *) ; 

void kvm_lapic_exit(void)
{
	static_key_deferred_flush(&apic_hw_disabled);
	static_key_deferred_flush(&apic_sw_disabled);
}