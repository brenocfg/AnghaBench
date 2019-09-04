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
struct device {int dummy; } ;
struct devfreq {int /*<<< orphan*/  nb; } ;

/* Variables and functions */
 int dev_pm_opp_register_notifier (struct device*,int /*<<< orphan*/ *) ; 

int devfreq_register_opp_notifier(struct device *dev, struct devfreq *devfreq)
{
	return dev_pm_opp_register_notifier(dev, &devfreq->nb);
}