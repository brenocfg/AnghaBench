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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int MLX4_EN_WRAP_AROUND_SEC ; 
 int /*<<< orphan*/  ULLONG_MAX ; 
 int div64_u64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  div_u64 (int,int) ; 
 unsigned long long fls64 (int) ; 
 int ilog2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 freq_to_shift(u16 freq)
{
	u32 freq_khz = freq * 1000;
	u64 max_val_cycles = freq_khz * 1000 * MLX4_EN_WRAP_AROUND_SEC;
	u64 max_val_cycles_rounded = 1ULL << fls64(max_val_cycles - 1);
	/* calculate max possible multiplier in order to fit in 64bit */
	u64 max_mul = div64_u64(ULLONG_MAX, max_val_cycles_rounded);

	/* This comes from the reverse of clocksource_khz2mult */
	return ilog2(div_u64(max_mul * freq_khz, 1000000));
}