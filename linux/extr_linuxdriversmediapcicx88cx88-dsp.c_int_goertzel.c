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
typedef  int u64 ;
typedef  size_t u32 ;
typedef  int s64 ;
typedef  int s32 ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,size_t) ; 
 int int_cos (size_t) ; 

__attribute__((used)) static u32 int_goertzel(s16 x[], u32 N, u32 freq)
{
	/*
	 * We use the Goertzel algorithm to determine the power of the
	 * given frequency in the signal
	 */
	s32 s_prev = 0;
	s32 s_prev2 = 0;
	s32 coeff = 2 * int_cos(freq);
	u32 i;

	u64 tmp;
	u32 divisor;

	for (i = 0; i < N; i++) {
		s32 s = x[i] + ((s64)coeff * s_prev / 32768) - s_prev2;

		s_prev2 = s_prev;
		s_prev = s;
	}

	tmp = (s64)s_prev2 * s_prev2 + (s64)s_prev * s_prev -
		      (s64)coeff * s_prev2 * s_prev / 32768;

	/*
	 * XXX: N must be low enough so that N*N fits in s32.
	 * Else we need two divisions.
	 */
	divisor = N * N;
	do_div(tmp, divisor);

	return (u32)tmp;
}