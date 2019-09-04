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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct devfreq {TYPE_1__ dev; } ;
struct dev_pm_opp {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dev_pm_opp*) ; 
 struct dev_pm_opp* dev_pm_opp_find_freq_ceil (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  dev_pm_opp_put (struct dev_pm_opp*) ; 

__attribute__((used)) static unsigned long find_available_min_freq(struct devfreq *devfreq)
{
	struct dev_pm_opp *opp;
	unsigned long min_freq = 0;

	opp = dev_pm_opp_find_freq_ceil(devfreq->dev.parent, &min_freq);
	if (IS_ERR(opp))
		min_freq = 0;
	else
		dev_pm_opp_put(opp);

	return min_freq;
}