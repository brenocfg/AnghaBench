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
struct am33xx_pm_platform_data {int dummy; } ;

/* Variables and functions */
 struct am33xx_pm_platform_data am33xx_ops ; 
 struct am33xx_pm_platform_data am43xx_ops ; 
 scalar_t__ soc_is_am33xx () ; 
 scalar_t__ soc_is_am437x () ; 

__attribute__((used)) static struct am33xx_pm_platform_data *am33xx_pm_get_pdata(void)
{
	if (soc_is_am33xx())
		return &am33xx_ops;
	else if (soc_is_am437x())
		return &am43xx_ops;
	else
		return NULL;
}