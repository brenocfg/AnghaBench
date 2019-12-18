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
struct shmob_drm_device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long jiffies ; 
 int lcdc_read (struct shmob_drm_device*,int) ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static inline int lcdc_wait_bit(struct shmob_drm_device *sdev, u32 reg,
				u32 mask, u32 until)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(5);

	while ((lcdc_read(sdev, reg) & mask) != until) {
		if (time_after(jiffies, timeout))
			return -ETIMEDOUT;
		cpu_relax();
	}

	return 0;
}