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

__attribute__((used)) static void physflat_init_apic_ldr(void)
{
	/*
	 * LDR and DFR are not involved in physflat mode, rather:
	 * "In physical destination mode, the destination processor is
	 * specified by its local APIC ID [...]." (Intel SDM, 10.6.2.1)
	 */
}