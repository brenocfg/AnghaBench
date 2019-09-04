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
 int /*<<< orphan*/  A ; 
 scalar_t__ A_c ; 
 int /*<<< orphan*/  B ; 
 scalar_t__ B_c ; 
 scalar_t__ B_s ; 
 int /*<<< orphan*/  C ; 
 scalar_t__ C_c ; 
 int /*<<< orphan*/  EFLAG_VXIMZ ; 
 int /*<<< orphan*/  EFLAG_VXISI ; 
 int /*<<< orphan*/  FP_ADD_D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FP_CLS_INF ; 
 scalar_t__ FP_CLS_NAN ; 
 scalar_t__ FP_CLS_ZERO ; 
 int FP_CUR_EXCEPTIONS ; 
 int /*<<< orphan*/  FP_DECL_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_MUL_D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_SET_EXCEPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_DP (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  R ; 
 scalar_t__ R_c ; 
 int R_s ; 
 int /*<<< orphan*/  T ; 
 scalar_t__ T_c ; 
 scalar_t__ T_s ; 
 int /*<<< orphan*/  __FP_PACK_DS (void*,int /*<<< orphan*/ ) ; 

int
fnmadds(void *frD, void *frA, void *frB, void *frC)
{
	FP_DECL_D(R);
	FP_DECL_D(A);
	FP_DECL_D(B);
	FP_DECL_D(C);
	FP_DECL_D(T);
	FP_DECL_EX;

#ifdef DEBUG
	printk("%s: %p %p %p %p\n", __func__, frD, frA, frB, frC);
#endif

	FP_UNPACK_DP(A, frA);
	FP_UNPACK_DP(B, frB);
	FP_UNPACK_DP(C, frC);

#ifdef DEBUG
	printk("A: %ld %lu %lu %ld (%ld)\n", A_s, A_f1, A_f0, A_e, A_c);
	printk("B: %ld %lu %lu %ld (%ld)\n", B_s, B_f1, B_f0, B_e, B_c);
	printk("C: %ld %lu %lu %ld (%ld)\n", C_s, C_f1, C_f0, C_e, C_c);
#endif

	if ((A_c == FP_CLS_INF && C_c == FP_CLS_ZERO) ||
	    (A_c == FP_CLS_ZERO && C_c == FP_CLS_INF))
                FP_SET_EXCEPTION(EFLAG_VXIMZ);

	FP_MUL_D(T, A, C);

	if (T_s != B_s && T_c == FP_CLS_INF && B_c == FP_CLS_INF)
		FP_SET_EXCEPTION(EFLAG_VXISI);

	FP_ADD_D(R, T, B);

	if (R_c != FP_CLS_NAN)
		R_s ^= 1;

#ifdef DEBUG
	printk("D: %ld %lu %lu %ld (%ld)\n", R_s, R_f1, R_f0, R_e, R_c);
#endif

	__FP_PACK_DS(frD, R);

	return FP_CUR_EXCEPTIONS;
}