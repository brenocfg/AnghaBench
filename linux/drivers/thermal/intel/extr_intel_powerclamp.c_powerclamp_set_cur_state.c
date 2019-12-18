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
struct thermal_cooling_device {int dummy; } ;

/* Variables and functions */
 int MAX_TARGET_RATIO ; 
 unsigned long clamp (unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  end_power_clamp () ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 unsigned long set_target_ratio ; 
 int /*<<< orphan*/  smp_mb () ; 
 int start_power_clamp () ; 

__attribute__((used)) static int powerclamp_set_cur_state(struct thermal_cooling_device *cdev,
				 unsigned long new_target_ratio)
{
	int ret = 0;

	new_target_ratio = clamp(new_target_ratio, 0UL,
				(unsigned long) (MAX_TARGET_RATIO-1));
	if (set_target_ratio == 0 && new_target_ratio > 0) {
		pr_info("Start idle injection to reduce power\n");
		set_target_ratio = new_target_ratio;
		ret = start_power_clamp();
		goto exit_set;
	} else	if (set_target_ratio > 0 && new_target_ratio == 0) {
		pr_info("Stop forced idle injection\n");
		end_power_clamp();
		set_target_ratio = 0;
	} else	/* adjust currently running */ {
		set_target_ratio = new_target_ratio;
		/* make new set_target_ratio visible to other cpus */
		smp_mb();
	}

exit_set:
	return ret;
}