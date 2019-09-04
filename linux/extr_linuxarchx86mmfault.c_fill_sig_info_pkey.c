#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ si_pkey; } ;
typedef  TYPE_1__ siginfo_t ;

/* Variables and functions */
 int SEGV_PKUERR ; 
 int SIGSEGV ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  X86_FEATURE_OSPKE ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fill_sig_info_pkey(int si_signo, int si_code, siginfo_t *info,
		u32 *pkey)
{
	/* This is effectively an #ifdef */
	if (!boot_cpu_has(X86_FEATURE_OSPKE))
		return;

	/* Fault not from Protection Keys: nothing to do */
	if ((si_code != SEGV_PKUERR) || (si_signo != SIGSEGV))
		return;
	/*
	 * force_sig_info_fault() is called from a number of
	 * contexts, some of which have a VMA and some of which
	 * do not.  The X86_PF_PK handing happens after we have a
	 * valid VMA, so we should never reach this without a
	 * valid VMA.
	 */
	if (!pkey) {
		WARN_ONCE(1, "PKU fault with no VMA passed in");
		info->si_pkey = 0;
		return;
	}
	/*
	 * si_pkey should be thought of as a strong hint, but not
	 * absolutely guranteed to be 100% accurate because of
	 * the race explained above.
	 */
	info->si_pkey = *pkey;
}