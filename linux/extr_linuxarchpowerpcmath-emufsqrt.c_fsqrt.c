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
 int /*<<< orphan*/  B ; 
 scalar_t__ B_c ; 
 scalar_t__ B_s ; 
 int /*<<< orphan*/  EFLAG_VXSNAN ; 
 int /*<<< orphan*/  EFLAG_VXSQRT ; 
 scalar_t__ FP_CLS_NAN ; 
 scalar_t__ FP_CLS_ZERO ; 
 int FP_CUR_EXCEPTIONS ; 
 int /*<<< orphan*/  FP_DECL_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_SET_EXCEPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_SQRT_D (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_DP (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  R ; 
 int /*<<< orphan*/  __FP_PACK_D (void*,int /*<<< orphan*/ ) ; 

int
fsqrt(void *frD, void *frB)
{
	FP_DECL_D(B);
	FP_DECL_D(R);
	FP_DECL_EX;

#ifdef DEBUG
	printk("%s: %p %p %p %p\n", __func__, frD, frB);
#endif

	FP_UNPACK_DP(B, frB);

#ifdef DEBUG
	printk("B: %ld %lu %lu %ld (%ld)\n", B_s, B_f1, B_f0, B_e, B_c);
#endif

	if (B_s && B_c != FP_CLS_ZERO)
		FP_SET_EXCEPTION(EFLAG_VXSQRT);
	if (B_c == FP_CLS_NAN)
		FP_SET_EXCEPTION(EFLAG_VXSNAN);

	FP_SQRT_D(R, B);

#ifdef DEBUG
	printk("R: %ld %lu %lu %ld (%ld)\n", R_s, R_f1, R_f0, R_e, R_c);
#endif

	__FP_PACK_D(frD, R);

	return FP_CUR_EXCEPTIONS;
}