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
struct platform_device {int dummy; } ;
struct TYPE_2__ {struct platform_device* of_dev; } ;

/* Variables and functions */
 TYPE_1__* smu ; 

struct platform_device *smu_get_ofdev(void)
{
	if (!smu)
		return NULL;
	return smu->of_dev;
}