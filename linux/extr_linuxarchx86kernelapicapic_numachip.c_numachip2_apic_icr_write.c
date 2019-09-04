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
 int /*<<< orphan*/  NUMACHIP2_APIC_ICR ; 
 int /*<<< orphan*/  numachip2_write32_lcsr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void numachip2_apic_icr_write(int apicid, unsigned int val)
{
	numachip2_write32_lcsr(NUMACHIP2_APIC_ICR, (apicid << 12) | val);
}