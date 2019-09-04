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
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpu_freq_write_amd(struct acpi_pct_register *not_used, u32 val)
{
	wrmsr(MSR_AMD_PERF_CTL, val, 0);
}