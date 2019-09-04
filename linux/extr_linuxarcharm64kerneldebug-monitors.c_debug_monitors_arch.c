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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ID_AA64DFR0_DEBUGVER_SHIFT ; 
 int /*<<< orphan*/  SYS_ID_AA64DFR0_EL1 ; 
 int /*<<< orphan*/  cpuid_feature_extract_unsigned_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_sanitised_ftr_reg (int /*<<< orphan*/ ) ; 

u8 debug_monitors_arch(void)
{
	return cpuid_feature_extract_unsigned_field(read_sanitised_ftr_reg(SYS_ID_AA64DFR0_EL1),
						ID_AA64DFR0_DEBUGVER_SHIFT);
}