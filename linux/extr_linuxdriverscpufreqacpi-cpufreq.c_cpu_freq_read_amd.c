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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_pct_register {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_AMD_PERF_CTL ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 cpu_freq_read_amd(struct acpi_pct_register *not_used)
{
	u32 val, dummy;

	rdmsr(MSR_AMD_PERF_CTL, val, dummy);
	return val;
}