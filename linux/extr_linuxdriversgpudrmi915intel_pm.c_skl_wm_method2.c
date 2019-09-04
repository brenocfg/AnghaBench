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
typedef  int /*<<< orphan*/  uint_fixed_16_16_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  FP_16_16_MAX ; 
 int /*<<< orphan*/  mul_u32_fixed16 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint_fixed_16_16_t skl_wm_method2(uint32_t pixel_rate,
			uint32_t pipe_htotal,
			uint32_t latency,
			uint_fixed_16_16_t plane_blocks_per_line)
{
	uint32_t wm_intermediate_val;
	uint_fixed_16_16_t ret;

	if (latency == 0)
		return FP_16_16_MAX;

	wm_intermediate_val = latency * pixel_rate;
	wm_intermediate_val = DIV_ROUND_UP(wm_intermediate_val,
					   pipe_htotal * 1000);
	ret = mul_u32_fixed16(wm_intermediate_val, plane_blocks_per_line);
	return ret;
}