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
struct etnaviv_gpu {int idle_mask; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  VIVS_HI_IDLE_STATE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int gpu_read (struct etnaviv_gpu*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned int) ; 
 scalar_t__ time_is_before_jiffies (unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

int etnaviv_gpu_wait_idle(struct etnaviv_gpu *gpu, unsigned int timeout_ms)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(timeout_ms);

	do {
		u32 idle = gpu_read(gpu, VIVS_HI_IDLE_STATE);

		if ((idle & gpu->idle_mask) == gpu->idle_mask)
			return 0;

		if (time_is_before_jiffies(timeout)) {
			dev_warn(gpu->dev,
				 "timed out waiting for idle: idle=0x%x\n",
				 idle);
			return -ETIMEDOUT;
		}

		udelay(5);
	} while (1);
}