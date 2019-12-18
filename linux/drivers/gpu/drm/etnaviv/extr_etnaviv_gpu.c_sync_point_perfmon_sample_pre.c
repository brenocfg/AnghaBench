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
typedef  int /*<<< orphan*/  u32 ;
struct etnaviv_gpu {int dummy; } ;
struct etnaviv_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETNA_PM_PROCESS_PRE ; 
 int /*<<< orphan*/  VIVS_HI_CLOCK_CONTROL ; 
 int /*<<< orphan*/  VIVS_HI_CLOCK_CONTROL_DISABLE_DEBUG_REGISTERS ; 
 int /*<<< orphan*/  VIVS_PM_POWER_CONTROLS ; 
 int /*<<< orphan*/  VIVS_PM_POWER_CONTROLS_ENABLE_MODULE_CLOCK_GATING ; 
 int /*<<< orphan*/  gpu_read (struct etnaviv_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct etnaviv_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_point_perfmon_sample (struct etnaviv_gpu*,struct etnaviv_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sync_point_perfmon_sample_pre(struct etnaviv_gpu *gpu,
	struct etnaviv_event *event)
{
	u32 val;

	/* disable clock gating */
	val = gpu_read(gpu, VIVS_PM_POWER_CONTROLS);
	val &= ~VIVS_PM_POWER_CONTROLS_ENABLE_MODULE_CLOCK_GATING;
	gpu_write(gpu, VIVS_PM_POWER_CONTROLS, val);

	/* enable debug register */
	val = gpu_read(gpu, VIVS_HI_CLOCK_CONTROL);
	val &= ~VIVS_HI_CLOCK_CONTROL_DISABLE_DEBUG_REGISTERS;
	gpu_write(gpu, VIVS_HI_CLOCK_CONTROL, val);

	sync_point_perfmon_sample(gpu, event, ETNA_PM_PROCESS_PRE);
}