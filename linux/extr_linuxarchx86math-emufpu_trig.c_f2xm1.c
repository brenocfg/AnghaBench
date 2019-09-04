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
typedef  int u_char ;
typedef  int /*<<< orphan*/  FPU_REG ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_1 ; 
 int FPU_Special (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FPU_copy_to_reg0 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FPU_to_exp16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int TAG_Special ; 
 int TAG_Valid ; 
 int TAG_Zero ; 
#define  TW_Denormal 129 
#define  TW_Infinity 128 
 int /*<<< orphan*/  clear_C1 () ; 
 int /*<<< orphan*/  denormal_operand () ; 
 scalar_t__ exponent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getsign (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poly_2xm1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_precision_flag_up () ; 
 int /*<<< orphan*/  setnegative (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signnegative (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  single_arg_error (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void f2xm1(FPU_REG *st0_ptr, u_char tag)
{
	FPU_REG a;

	clear_C1();

	if (tag == TAG_Valid) {
		/* For an 80486 FPU, the result is undefined if the arg is >= 1.0 */
		if (exponent(st0_ptr) < 0) {
		      denormal_arg:

			FPU_to_exp16(st0_ptr, &a);

			/* poly_2xm1(x) requires 0 < st(0) < 1. */
			poly_2xm1(getsign(st0_ptr), &a, st0_ptr);
		}
		set_precision_flag_up();	/* 80486 appears to always do this */
		return;
	}

	if (tag == TAG_Zero)
		return;

	if (tag == TAG_Special)
		tag = FPU_Special(st0_ptr);

	switch (tag) {
	case TW_Denormal:
		if (denormal_operand() < 0)
			return;
		goto denormal_arg;
	case TW_Infinity:
		if (signnegative(st0_ptr)) {
			/* -infinity gives -1 (p16-10) */
			FPU_copy_to_reg0(&CONST_1, TAG_Valid);
			setnegative(st0_ptr);
		}
		return;
	default:
		single_arg_error(st0_ptr, tag);
	}
}