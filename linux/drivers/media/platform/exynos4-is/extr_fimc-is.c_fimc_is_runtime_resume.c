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
struct fimc_is {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct fimc_is* dev_get_drvdata (struct device*) ; 
 int fimc_is_enable_clocks (struct fimc_is*) ; 
 int fimc_is_setup_clocks (struct fimc_is*) ; 

__attribute__((used)) static int fimc_is_runtime_resume(struct device *dev)
{
	struct fimc_is *is = dev_get_drvdata(dev);
	int ret;

	ret = fimc_is_setup_clocks(is);
	if (ret)
		return ret;

	return fimc_is_enable_clocks(is);
}