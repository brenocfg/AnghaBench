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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_CR_PAT ; 
 int /*<<< orphan*/  X86_FEATURE_PAT ; 
 int /*<<< orphan*/  __init_cache_modes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pat_disable (char*) ; 
 int pat_initialized ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pat_bsp_init(u64 pat)
{
	u64 tmp_pat;

	if (!boot_cpu_has(X86_FEATURE_PAT)) {
		pat_disable("PAT not supported by CPU.");
		return;
	}

	rdmsrl(MSR_IA32_CR_PAT, tmp_pat);
	if (!tmp_pat) {
		pat_disable("PAT MSR is 0, disabled.");
		return;
	}

	wrmsrl(MSR_IA32_CR_PAT, pat);
	pat_initialized = true;

	__init_cache_modes(pat);
}