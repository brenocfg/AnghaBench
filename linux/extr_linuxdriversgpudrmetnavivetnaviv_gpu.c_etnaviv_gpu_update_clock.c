#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int minor_features2; } ;
struct etnaviv_gpu {int base_rate_core; int freq_scale; int base_rate_shader; int /*<<< orphan*/  clk_shader; int /*<<< orphan*/  clk_core; TYPE_1__ identity; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIVS_HI_CLOCK_CONTROL ; 
 int /*<<< orphan*/  VIVS_HI_CLOCK_CONTROL_FSCALE_VAL (unsigned int) ; 
 int /*<<< orphan*/  VIVS_HI_CLOCK_CONTROL_FSCALE_VAL__MASK ; 
 int chipMinorFeatures2_DYNAMIC_FREQUENCY_SCALING ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  etnaviv_gpu_load_clock (struct etnaviv_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_read (struct etnaviv_gpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void etnaviv_gpu_update_clock(struct etnaviv_gpu *gpu)
{
	if (gpu->identity.minor_features2 &
	    chipMinorFeatures2_DYNAMIC_FREQUENCY_SCALING) {
		clk_set_rate(gpu->clk_core,
			     gpu->base_rate_core >> gpu->freq_scale);
		clk_set_rate(gpu->clk_shader,
			     gpu->base_rate_shader >> gpu->freq_scale);
	} else {
		unsigned int fscale = 1 << (6 - gpu->freq_scale);
		u32 clock = gpu_read(gpu, VIVS_HI_CLOCK_CONTROL);

		clock &= ~VIVS_HI_CLOCK_CONTROL_FSCALE_VAL__MASK;
		clock |= VIVS_HI_CLOCK_CONTROL_FSCALE_VAL(fscale);
		etnaviv_gpu_load_clock(gpu, clock);
	}
}