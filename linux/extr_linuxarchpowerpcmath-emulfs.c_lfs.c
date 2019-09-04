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
 scalar_t__ FP_CLS_NAN ; 
 int /*<<< orphan*/  FP_CONV (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_DECL_S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_S (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  R ; 
 scalar_t__ R_c ; 
 int /*<<< orphan*/  R_e ; 
 int /*<<< orphan*/  S ; 
 int /*<<< orphan*/  _FP_EXPMAX_D ; 
 int /*<<< orphan*/  _FP_PACK_RAW_2_P (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __FP_PACK_D (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_from_user (float*,void*,int) ; 

int
lfs(void *frD, void *ea)
{
	FP_DECL_D(R);
	FP_DECL_S(A);
	FP_DECL_EX;
	float f;

#ifdef DEBUG
	printk("%s: D %p, ea %p\n", __func__, frD, ea);
#endif

	if (copy_from_user(&f, ea, sizeof(float)))
		return -EFAULT;

	FP_UNPACK_S(A, f);

#ifdef DEBUG
	printk("A: %ld %lu %ld (%ld) [%08lx]\n", A_s, A_f, A_e, A_c,
	       *(unsigned long *)&f);
#endif

	FP_CONV(D, S, 2, 1, R, A);

#ifdef DEBUG
	printk("R: %ld %lu %lu %ld (%ld)\n", R_s, R_f1, R_f0, R_e, R_c);
#endif

	if (R_c == FP_CLS_NAN) {
		R_e = _FP_EXPMAX_D;
		_FP_PACK_RAW_2_P(D, frD, R);
	} else {
		__FP_PACK_D(frD, R);
	}

	return 0;
}