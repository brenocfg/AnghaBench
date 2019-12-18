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

/* Variables and functions */
 int _opp_set_availability (struct device*,unsigned long,int) ; 

int dev_pm_opp_enable(struct device *dev, unsigned long freq)
{
	return _opp_set_availability(dev, freq, true);
}