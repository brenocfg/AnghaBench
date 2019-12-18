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
struct fixed31_32 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  compute_de_pq (struct fixed31_32,struct fixed31_32*) ; 
 int /*<<< orphan*/  compute_pq (struct fixed31_32,struct fixed31_32*) ; 
 struct fixed31_32 dc_fixpt_add (struct fixed31_32,struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_div (struct fixed31_32,struct fixed31_32) ; 
 scalar_t__ dc_fixpt_eq (struct fixed31_32,struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_from_fraction (int,int) ; 
 struct fixed31_32 dc_fixpt_from_int (int) ; 
 scalar_t__ dc_fixpt_le (struct fixed31_32,struct fixed31_32) ; 
 scalar_t__ dc_fixpt_lt (struct fixed31_32,struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_mul (struct fixed31_32,struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_one ; 
 struct fixed31_32 dc_fixpt_sub (struct fixed31_32,struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_zero ; 

__attribute__((used)) static void hermite_spline_eetf(struct fixed31_32 input_x,
				struct fixed31_32 max_display,
				struct fixed31_32 min_display,
				struct fixed31_32 max_content,
				struct fixed31_32 *out_x)
{
	struct fixed31_32 min_lum_pq;
	struct fixed31_32 max_lum_pq;
	struct fixed31_32 max_content_pq;
	struct fixed31_32 ks;
	struct fixed31_32 E1;
	struct fixed31_32 E2;
	struct fixed31_32 E3;
	struct fixed31_32 t;
	struct fixed31_32 t2;
	struct fixed31_32 t3;
	struct fixed31_32 two;
	struct fixed31_32 three;
	struct fixed31_32 temp1;
	struct fixed31_32 temp2;
	struct fixed31_32 a = dc_fixpt_from_fraction(15, 10);
	struct fixed31_32 b = dc_fixpt_from_fraction(5, 10);
	struct fixed31_32 epsilon = dc_fixpt_from_fraction(1, 1000000); // dc_fixpt_epsilon is a bit too small

	if (dc_fixpt_eq(max_content, dc_fixpt_zero)) {
		*out_x = dc_fixpt_zero;
		return;
	}

	compute_pq(input_x, &E1);
	compute_pq(dc_fixpt_div(min_display, max_content), &min_lum_pq);
	compute_pq(dc_fixpt_div(max_display, max_content), &max_lum_pq);
	compute_pq(dc_fixpt_one, &max_content_pq); // always 1? DAL2 code is weird
	a = dc_fixpt_div(dc_fixpt_add(dc_fixpt_one, b), max_content_pq); // (1+b)/maxContent
	ks = dc_fixpt_sub(dc_fixpt_mul(a, max_lum_pq), b); // a * max_lum_pq - b

	if (dc_fixpt_lt(E1, ks))
		E2 = E1;
	else if (dc_fixpt_le(ks, E1) && dc_fixpt_le(E1, dc_fixpt_one)) {
		if (dc_fixpt_lt(epsilon, dc_fixpt_sub(dc_fixpt_one, ks)))
			// t = (E1 - ks) / (1 - ks)
			t = dc_fixpt_div(dc_fixpt_sub(E1, ks),
					dc_fixpt_sub(dc_fixpt_one, ks));
		else
			t = dc_fixpt_zero;

		two = dc_fixpt_from_int(2);
		three = dc_fixpt_from_int(3);

		t2 = dc_fixpt_mul(t, t);
		t3 = dc_fixpt_mul(t2, t);
		temp1 = dc_fixpt_mul(two, t3);
		temp2 = dc_fixpt_mul(three, t2);

		// (2t^3 - 3t^2 + 1) * ks
		E2 = dc_fixpt_mul(ks, dc_fixpt_add(dc_fixpt_one,
				dc_fixpt_sub(temp1, temp2)));

		// (-2t^3 + 3t^2) * max_lum_pq
		E2 = dc_fixpt_add(E2, dc_fixpt_mul(max_lum_pq,
				dc_fixpt_sub(temp2, temp1)));

		temp1 = dc_fixpt_mul(two, t2);
		temp2 = dc_fixpt_sub(dc_fixpt_one, ks);

		// (t^3 - 2t^2 + t) * (1-ks)
		E2 = dc_fixpt_add(E2, dc_fixpt_mul(temp2,
				dc_fixpt_add(t, dc_fixpt_sub(t3, temp1))));
	} else
		E2 = dc_fixpt_one;

	temp1 = dc_fixpt_sub(dc_fixpt_one, E2);
	temp2 = dc_fixpt_mul(temp1, temp1);
	temp2 = dc_fixpt_mul(temp2, temp2);
	// temp2 = (1-E2)^4

	E3 =  dc_fixpt_add(E2, dc_fixpt_mul(min_lum_pq, temp2));
	compute_de_pq(E3, out_x);

	*out_x = dc_fixpt_div(*out_x, dc_fixpt_div(max_display, max_content));
}