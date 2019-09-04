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
 int /*<<< orphan*/  MMU_FTR_68_BIT_VA ; 
 int MMU_SEGSIZE_256M ; 
 unsigned long SID_SHIFT ; 
 unsigned long SID_SHIFT_1T ; 
 unsigned long VA_BITS ; 
 unsigned long VSID_MULINV_1T ; 
 unsigned long VSID_MULINV_256M ; 
 int /*<<< orphan*/  mmu_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long vsid_unscramble(unsigned long vsid, int ssize)
{
	unsigned long protovsid;
	unsigned long va_bits = VA_BITS;
	unsigned long modinv, vsid_modulus;
	unsigned long max_mod_inv, tmp_modinv;

	if (!mmu_has_feature(MMU_FTR_68_BIT_VA))
		va_bits = 65;

	if (ssize == MMU_SEGSIZE_256M) {
		modinv = VSID_MULINV_256M;
		vsid_modulus = ((1UL << (va_bits - SID_SHIFT)) - 1);
	} else {
		modinv = VSID_MULINV_1T;
		vsid_modulus = ((1UL << (va_bits - SID_SHIFT_1T)) - 1);
	}

	/*
	 * vsid outside our range.
	 */
	if (vsid >= vsid_modulus)
		return 0;

	/*
	 * If modinv is the modular multiplicate inverse of (x % vsid_modulus)
	 * and vsid = (protovsid * x) % vsid_modulus, then we say:
	 *   protovsid = (vsid * modinv) % vsid_modulus
	 */

	/* Check if (vsid * modinv) overflow (63 bits) */
	max_mod_inv = 0x7fffffffffffffffull / vsid;
	if (modinv < max_mod_inv)
		return (vsid * modinv) % vsid_modulus;

	tmp_modinv = modinv/max_mod_inv;
	modinv %= max_mod_inv;

	protovsid = (((vsid * max_mod_inv) % vsid_modulus) * tmp_modinv) % vsid_modulus;
	protovsid = (protovsid + vsid * modinv) % vsid_modulus;

	return protovsid;
}