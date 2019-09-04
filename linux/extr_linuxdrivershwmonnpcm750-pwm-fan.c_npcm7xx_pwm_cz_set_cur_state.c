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
struct thermal_cooling_device {struct npcm7xx_cooling_device* devdata; } ;
struct npcm7xx_cooling_device {unsigned long max_state; unsigned long cur_state; int /*<<< orphan*/ * cooling_levels; int /*<<< orphan*/  pwm_port; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EINVAL ; 
 int npcm7xx_pwm_config_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
npcm7xx_pwm_cz_set_cur_state(struct thermal_cooling_device *tcdev,
			     unsigned long state)
{
	struct npcm7xx_cooling_device *cdev = tcdev->devdata;
	int ret;

	if (state > cdev->max_state)
		return -EINVAL;

	cdev->cur_state = state;
	ret = npcm7xx_pwm_config_set(cdev->data, cdev->pwm_port,
				     cdev->cooling_levels[cdev->cur_state]);

	return ret;
}