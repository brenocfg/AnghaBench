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
struct msm_gpu {int /*<<< orphan*/  core_clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 struct msm_gpu* platform_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_platform_device (struct device*) ; 

__attribute__((used)) static int msm_devfreq_get_cur_freq(struct device *dev, unsigned long *freq)
{
	struct msm_gpu *gpu = platform_get_drvdata(to_platform_device(dev));

	*freq = (unsigned long) clk_get_rate(gpu->core_clk);

	return 0;
}