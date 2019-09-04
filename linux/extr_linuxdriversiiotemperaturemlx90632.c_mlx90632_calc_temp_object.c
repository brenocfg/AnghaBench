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
typedef  int /*<<< orphan*/  u16 ;
typedef  int s8 ;
typedef  long long s64 ;
typedef  long long s32 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 long long div64_s64 (long long,long long) ; 
 long long mlx90632_calc_temp_object_iteration (long long,long long,long long,long long,long long,long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 mlx90632_calc_temp_object(s64 object, s64 ambient, s32 Ea, s32 Eb,
				     s32 Fa, s32 Fb, s32 Ga, s16 Ha, s16 Hb,
				     u16 tmp_emi)
{
	s64 kTA, kTA0, TAdut;
	s64 temp = 25000;
	s8 i;

	kTA = (Ea * 1000LL) >> 16LL;
	kTA0 = (Eb * 1000LL) >> 8LL;
	TAdut = div64_s64(((ambient - kTA0) * 1000000LL), kTA) + 25 * 1000000LL;

	/* Iterations of calculation as described in datasheet */
	for (i = 0; i < 5; ++i) {
		temp = mlx90632_calc_temp_object_iteration(temp, object, TAdut,
							   Fa, Fb, Ga, Ha, Hb,
							   tmp_emi);
	}
	return temp;
}