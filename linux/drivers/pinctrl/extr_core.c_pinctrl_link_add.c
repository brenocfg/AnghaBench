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
struct pinctrl_dev {int /*<<< orphan*/  dev; TYPE_1__* desc; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ link_consumers; } ;

/* Variables and functions */
 int DL_FLAG_AUTOREMOVE_CONSUMER ; 
 int DL_FLAG_PM_RUNTIME ; 
 int /*<<< orphan*/  device_link_add (struct device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pinctrl_link_add(struct pinctrl_dev *pctldev,
			     struct device *consumer)
{
	if (pctldev->desc->link_consumers)
		device_link_add(consumer, pctldev->dev,
				DL_FLAG_PM_RUNTIME |
				DL_FLAG_AUTOREMOVE_CONSUMER);
}