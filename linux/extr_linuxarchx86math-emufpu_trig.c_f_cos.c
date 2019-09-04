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
typedef  scalar_t__ u_char ;
typedef  int /*<<< orphan*/  FPU_REG ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_1 ; 
 int /*<<< orphan*/  FCOS ; 
 scalar_t__ FPU_Special (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FPU_copy_to_reg0 (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ TAG_Special ; 
 scalar_t__ TAG_Valid ; 
 scalar_t__ TAG_Zero ; 
 scalar_t__ TW_Denormal ; 
 scalar_t__ TW_Infinity ; 
 int /*<<< orphan*/  arith_invalid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  changesign (int /*<<< orphan*/ *) ; 
 scalar_t__ denormal_operand () ; 
 int exponent (int /*<<< orphan*/ *) ; 
 scalar_t__ getsign (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poly_cos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poly_sine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_precision_flag_down () ; 
 int /*<<< orphan*/  set_precision_flag_up () ; 
 int /*<<< orphan*/  setcc (int /*<<< orphan*/ ) ; 
 int significand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  single_arg_error (int /*<<< orphan*/ *,scalar_t__) ; 
 int trig_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f_cos(FPU_REG *st0_ptr, u_char tag)
{
	u_char st0_sign;

	st0_sign = getsign(st0_ptr);

	if (tag == TAG_Valid) {
		int q;

		if (exponent(st0_ptr) > -40) {
			if ((exponent(st0_ptr) < 0)
			    || ((exponent(st0_ptr) == 0)
				&& (significand(st0_ptr) <=
				    0xc90fdaa22168c234LL))) {
				poly_cos(st0_ptr);

				/* We do not really know if up or down */
				set_precision_flag_down();

				return 0;
			} else if ((q = trig_arg(st0_ptr, FCOS)) != -1) {
				poly_sine(st0_ptr);

				if ((q + 1) & 2)
					changesign(st0_ptr);

				/* We do not really know if up or down */
				set_precision_flag_down();

				return 0;
			} else {
				/* Operand is out of range */
				return 1;
			}
		} else {
		      denormal_arg:

			setcc(0);
			FPU_copy_to_reg0(&CONST_1, TAG_Valid);
#ifdef PECULIAR_486
			set_precision_flag_down();	/* 80486 appears to do this. */
#else
			set_precision_flag_up();	/* Must be up. */
#endif /* PECULIAR_486 */
			return 0;
		}
	} else if (tag == TAG_Zero) {
		FPU_copy_to_reg0(&CONST_1, TAG_Valid);
		setcc(0);
		return 0;
	}

	if (tag == TAG_Special)
		tag = FPU_Special(st0_ptr);

	if (tag == TW_Denormal) {
		if (denormal_operand() < 0)
			return 1;

		goto denormal_arg;
	} else if (tag == TW_Infinity) {
		/* The 80486 treats infinity as an invalid operand */
		arith_invalid(0);
		return 1;
	} else {
		single_arg_error(st0_ptr, tag);	/* requires st0_ptr == &st(0) */
		return 1;
	}
}