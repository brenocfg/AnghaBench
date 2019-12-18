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
struct clock_cooling_device {unsigned long clock_state; unsigned long clock_val; int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long clock_cooling_get_frequency (struct clock_cooling_device*,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int clock_cooling_apply(struct clock_cooling_device *ccdev,
			       unsigned long cooling_state)
{
	unsigned long clip_freq, cur_freq;
	int ret = 0;

	/* Here we write the clipping */
	/* Check if the old cooling action is same as new cooling action */
	if (ccdev->clock_state == cooling_state)
		return 0;

	clip_freq = clock_cooling_get_frequency(ccdev, cooling_state);
	if (!clip_freq)
		return -EINVAL;

	cur_freq = clk_get_rate(ccdev->clk);

	mutex_lock(&ccdev->lock);
	ccdev->clock_state = cooling_state;
	ccdev->clock_val = clip_freq;
	/* enforce clock level */
	if (cur_freq > clip_freq)
		ret = clk_set_rate(ccdev->clk, clip_freq);
	mutex_unlock(&ccdev->lock);

	return ret;
}