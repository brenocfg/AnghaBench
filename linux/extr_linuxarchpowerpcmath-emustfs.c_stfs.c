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
 int /*<<< orphan*/  D ; 
 int EFAULT ; 
 int /*<<< orphan*/  FP_CONV (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FP_CUR_EXCEPTIONS ; 
 int /*<<< orphan*/  FP_DECL_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_DECL_S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_DP (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  R ; 
 int /*<<< orphan*/  S ; 
 int /*<<< orphan*/  _FP_PACK_CANONICAL (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FP_PACK_RAW_1_P (int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __FPU_TRAP_P (int) ; 
 scalar_t__ copy_to_user (void*,float*,int) ; 

int
stfs(void *frS, void *ea)
{
	FP_DECL_D(A);
	FP_DECL_S(R);
	FP_DECL_EX;
	float f;

#ifdef DEBUG
	printk("%s: S %p, ea %p\n", __func__, frS, ea);
#endif

	FP_UNPACK_DP(A, frS);

#ifdef DEBUG
	printk("A: %ld %lu %lu %ld (%ld)\n", A_s, A_f1, A_f0, A_e, A_c);
#endif

	FP_CONV(S, D, 1, 2, R, A);

#ifdef DEBUG
	printk("R: %ld %lu %ld (%ld)\n", R_s, R_f, R_e, R_c);
#endif

	_FP_PACK_CANONICAL(S, 1, R);
	if (!FP_CUR_EXCEPTIONS || !__FPU_TRAP_P(FP_CUR_EXCEPTIONS)) {
		_FP_PACK_RAW_1_P(S, &f, R);
		if (copy_to_user(ea, &f, sizeof(float)))
			return -EFAULT;
	}

	return FP_CUR_EXCEPTIONS;
}