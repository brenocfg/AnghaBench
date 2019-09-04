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
 int A_s ; 
 int /*<<< orphan*/  B ; 
 scalar_t__ B_c ; 
 int B_s ; 
 int /*<<< orphan*/  EFLAG_VXISI ; 
 int /*<<< orphan*/  FP_ADD_D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FP_CLS_INF ; 
 scalar_t__ FP_CLS_NAN ; 
 int FP_CUR_EXCEPTIONS ; 
 int /*<<< orphan*/  FP_DECL_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_SET_EXCEPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_DP (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  R ; 
 int /*<<< orphan*/  __FP_PACK_D (void*,int /*<<< orphan*/ ) ; 

int
fsub(void *frD, void *frA, void *frB)
{
	FP_DECL_D(A);
	FP_DECL_D(B);
	FP_DECL_D(R);
	FP_DECL_EX;

#ifdef DEBUG
	printk("%s: %p %p %p\n", __func__, frD, frA, frB);
#endif

	FP_UNPACK_DP(A, frA);
	FP_UNPACK_DP(B, frB);

#ifdef DEBUG
	printk("A: %ld %lu %lu %ld (%ld)\n", A_s, A_f1, A_f0, A_e, A_c);
	printk("B: %ld %lu %lu %ld (%ld)\n", B_s, B_f1, B_f0, B_e, B_c);
#endif

	if (B_c != FP_CLS_NAN)
		B_s ^= 1;

	if (A_s != B_s && A_c == FP_CLS_INF && B_c == FP_CLS_INF)
		FP_SET_EXCEPTION(EFLAG_VXISI);

	FP_ADD_D(R, A, B);

#ifdef DEBUG
	printk("D: %ld %lu %lu %ld (%ld)\n", R_s, R_f1, R_f0, R_e, R_c);
#endif

	__FP_PACK_D(frD, R);

	return FP_CUR_EXCEPTIONS;
}