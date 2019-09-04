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
typedef  scalar_t__ u64 ;
struct cpuinfo_x86 {int x86_phys_bits; } ;

/* Variables and functions */
 scalar_t__ MKTME_DISABLED ; 
 scalar_t__ MKTME_ENABLED ; 
 scalar_t__ MKTME_UNINITIALIZED ; 
 int /*<<< orphan*/  MSR_IA32_TME_ACTIVATE ; 
 scalar_t__ TME_ACTIVATE_CRYPTO_AES_XTS_128 ; 
 scalar_t__ TME_ACTIVATE_CRYPTO_ALGS (scalar_t__) ; 
 int /*<<< orphan*/  TME_ACTIVATE_ENABLED (scalar_t__) ; 
 int TME_ACTIVATE_KEYID_BITS (scalar_t__) ; 
 int /*<<< orphan*/  TME_ACTIVATE_LOCKED (scalar_t__) ; 
 scalar_t__ TME_ACTIVATE_POLICY (scalar_t__) ; 
 scalar_t__ TME_ACTIVATE_POLICY_AES_XTS_128 ; 
 scalar_t__ mktme_status ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err_once (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_info_once (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void detect_tme(struct cpuinfo_x86 *c)
{
	u64 tme_activate, tme_policy, tme_crypto_algs;
	int keyid_bits = 0, nr_keyids = 0;
	static u64 tme_activate_cpu0 = 0;

	rdmsrl(MSR_IA32_TME_ACTIVATE, tme_activate);

	if (mktme_status != MKTME_UNINITIALIZED) {
		if (tme_activate != tme_activate_cpu0) {
			/* Broken BIOS? */
			pr_err_once("x86/tme: configuration is inconsistent between CPUs\n");
			pr_err_once("x86/tme: MKTME is not usable\n");
			mktme_status = MKTME_DISABLED;

			/* Proceed. We may need to exclude bits from x86_phys_bits. */
		}
	} else {
		tme_activate_cpu0 = tme_activate;
	}

	if (!TME_ACTIVATE_LOCKED(tme_activate) || !TME_ACTIVATE_ENABLED(tme_activate)) {
		pr_info_once("x86/tme: not enabled by BIOS\n");
		mktme_status = MKTME_DISABLED;
		return;
	}

	if (mktme_status != MKTME_UNINITIALIZED)
		goto detect_keyid_bits;

	pr_info("x86/tme: enabled by BIOS\n");

	tme_policy = TME_ACTIVATE_POLICY(tme_activate);
	if (tme_policy != TME_ACTIVATE_POLICY_AES_XTS_128)
		pr_warn("x86/tme: Unknown policy is active: %#llx\n", tme_policy);

	tme_crypto_algs = TME_ACTIVATE_CRYPTO_ALGS(tme_activate);
	if (!(tme_crypto_algs & TME_ACTIVATE_CRYPTO_AES_XTS_128)) {
		pr_err("x86/mktme: No known encryption algorithm is supported: %#llx\n",
				tme_crypto_algs);
		mktme_status = MKTME_DISABLED;
	}
detect_keyid_bits:
	keyid_bits = TME_ACTIVATE_KEYID_BITS(tme_activate);
	nr_keyids = (1UL << keyid_bits) - 1;
	if (nr_keyids) {
		pr_info_once("x86/mktme: enabled by BIOS\n");
		pr_info_once("x86/mktme: %d KeyIDs available\n", nr_keyids);
	} else {
		pr_info_once("x86/mktme: disabled by BIOS\n");
	}

	if (mktme_status == MKTME_UNINITIALIZED) {
		/* MKTME is usable */
		mktme_status = MKTME_ENABLED;
	}

	/*
	 * KeyID bits effectively lower the number of physical address
	 * bits.  Update cpuinfo_x86::x86_phys_bits accordingly.
	 */
	c->x86_phys_bits -= keyid_bits;
}