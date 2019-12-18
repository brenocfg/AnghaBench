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
typedef  int u32 ;
struct etnaviv_gpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIVS_HI_CLOCK_CONTROL ; 
 int VIVS_HI_CLOCK_CONTROL_FSCALE_CMD_LOAD ; 
 int /*<<< orphan*/  gpu_write (struct etnaviv_gpu*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void etnaviv_gpu_load_clock(struct etnaviv_gpu *gpu, u32 clock)
{
	gpu_write(gpu, VIVS_HI_CLOCK_CONTROL, clock |
		  VIVS_HI_CLOCK_CONTROL_FSCALE_CMD_LOAD);
	gpu_write(gpu, VIVS_HI_CLOCK_CONTROL, clock);
}