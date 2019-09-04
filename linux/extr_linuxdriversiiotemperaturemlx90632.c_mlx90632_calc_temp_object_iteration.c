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
typedef  int u16 ;
typedef  long long s64 ;
typedef  int s32 ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int div64_s64 (long long,long long) ; 
 int int_sqrt64 (int) ; 

__attribute__((used)) static s32 mlx90632_calc_temp_object_iteration(s32 prev_object_temp, s64 object,
					       s64 TAdut, s32 Fa, s32 Fb,
					       s32 Ga, s16 Ha, s16 Hb,
					       u16 emissivity)
{
	s64 calcedKsTO, calcedKsTA, ir_Alpha, TAdut4, Alpha_corr;
	s64 Ha_customer, Hb_customer;

	Ha_customer = ((s64)Ha * 1000000LL) >> 14ULL;
	Hb_customer = ((s64)Hb * 100) >> 10ULL;

	calcedKsTO = ((s64)((s64)Ga * (prev_object_temp - 25 * 1000LL)
			     * 1000LL)) >> 36LL;
	calcedKsTA = ((s64)(Fb * (TAdut - 25 * 1000000LL))) >> 36LL;
	Alpha_corr = div64_s64((((s64)(Fa * 10000000000LL) >> 46LL)
				* Ha_customer), 1000LL);
	Alpha_corr *= ((s64)(1 * 1000000LL + calcedKsTO + calcedKsTA));
	Alpha_corr = emissivity * div64_s64(Alpha_corr, 100000LL);
	Alpha_corr = div64_s64(Alpha_corr, 1000LL);
	ir_Alpha = div64_s64((s64)object * 10000000LL, Alpha_corr);
	TAdut4 = (div64_s64(TAdut, 10000LL) + 27315) *
		(div64_s64(TAdut, 10000LL) + 27315) *
		(div64_s64(TAdut, 10000LL)  + 27315) *
		(div64_s64(TAdut, 10000LL) + 27315);

	return (int_sqrt64(int_sqrt64(ir_Alpha * 1000000000000LL + TAdut4))
		- 27315 - Hb_customer) * 10;
}