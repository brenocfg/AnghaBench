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
struct TYPE_2__ {unsigned long cur_freq; } ;
struct panfrost_device {TYPE_1__ devfreq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct panfrost_device* platform_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_platform_device (struct device*) ; 

__attribute__((used)) static int panfrost_devfreq_get_cur_freq(struct device *dev, unsigned long *freq)
{
	struct panfrost_device *pfdev = platform_get_drvdata(to_platform_device(dev));

	*freq = pfdev->devfreq.cur_freq;

	return 0;
}