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
 int /*<<< orphan*/  B ; 
 int /*<<< orphan*/  FP_ADD_D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FP_CUR_EXCEPTIONS ; 
 int /*<<< orphan*/  FP_DECL_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_UNPACK_DP (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  R ; 
 int /*<<< orphan*/  __FP_PACK_DS (void*,int /*<<< orphan*/ ) ; 

int
fadds(void *frD, void *frA, void *frB)
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

	FP_ADD_D(R, A, B);

#ifdef DEBUG
	printk("D: %ld %lu %lu %ld (%ld)\n", R_s, R_f1, R_f0, R_e, R_c);
#endif

	__FP_PACK_DS(frD, R);

	return FP_CUR_EXCEPTIONS;
}