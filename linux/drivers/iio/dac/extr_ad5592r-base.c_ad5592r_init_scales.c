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
struct ad5592r_state {void*** scale_avail; } ;
typedef  long long s64 ;

/* Variables and functions */
 void* div_s64_rem (long long,long long,void**) ; 

__attribute__((used)) static void ad5592r_init_scales(struct ad5592r_state *st, int vref_mV)
{
	s64 tmp = (s64)vref_mV * 1000000000LL >> 12;

	st->scale_avail[0][0] =
		div_s64_rem(tmp, 1000000000LL, &st->scale_avail[0][1]);
	st->scale_avail[1][0] =
		div_s64_rem(tmp * 2, 1000000000LL, &st->scale_avail[1][1]);
}