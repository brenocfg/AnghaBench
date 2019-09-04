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
struct devfreq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devfreq_remove_device (struct devfreq*) ; 

__attribute__((used)) static void devm_devfreq_dev_release(struct device *dev, void *res)
{
	devfreq_remove_device(*(struct devfreq **)res);
}