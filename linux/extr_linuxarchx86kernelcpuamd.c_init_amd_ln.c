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
struct cpuinfo_x86 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_AMD64_DE_CFG ; 
 int /*<<< orphan*/  msr_set_bit (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_amd_ln(struct cpuinfo_x86 *c)
{
	/*
	 * Apply erratum 665 fix unconditionally so machines without a BIOS
	 * fix work.
	 */
	msr_set_bit(MSR_AMD64_DE_CFG, 31);
}