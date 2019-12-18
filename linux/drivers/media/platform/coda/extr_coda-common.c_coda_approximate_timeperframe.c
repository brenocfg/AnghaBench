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
struct v4l2_fract {int member_0; int member_1; int numerator; int denominator; } ;

/* Variables and functions */
 unsigned int gcd (int,int) ; 

__attribute__((used)) static void coda_approximate_timeperframe(struct v4l2_fract *timeperframe)
{
	struct v4l2_fract s = *timeperframe;
	struct v4l2_fract f0;
	struct v4l2_fract f1 = { 1, 0 };
	struct v4l2_fract f2 = { 0, 1 };
	unsigned int i, div, s_denominator;

	/* Lower bound is 1/65535 */
	if (s.numerator == 0 || s.denominator / s.numerator > 65535) {
		timeperframe->numerator = 1;
		timeperframe->denominator = 65535;
		return;
	}

	/* Upper bound is 65536/1 */
	if (s.denominator == 0 || s.numerator / s.denominator > 65536) {
		timeperframe->numerator = 65536;
		timeperframe->denominator = 1;
		return;
	}

	/* Reduce fraction to lowest terms */
	div = gcd(s.numerator, s.denominator);
	if (div > 1) {
		s.numerator /= div;
		s.denominator /= div;
	}

	if (s.numerator <= 65536 && s.denominator < 65536) {
		*timeperframe = s;
		return;
	}

	/* Find successive convergents from continued fraction expansion */
	while (f2.numerator <= 65536 && f2.denominator < 65536) {
		f0 = f1;
		f1 = f2;

		/* Stop when f2 exactly equals timeperframe */
		if (s.numerator == 0)
			break;

		i = s.denominator / s.numerator;

		f2.numerator = f0.numerator + i * f1.numerator;
		f2.denominator = f0.denominator + i * f2.denominator;

		s_denominator = s.numerator;
		s.numerator = s.denominator % s.numerator;
		s.denominator = s_denominator;
	}

	*timeperframe = f1;
}