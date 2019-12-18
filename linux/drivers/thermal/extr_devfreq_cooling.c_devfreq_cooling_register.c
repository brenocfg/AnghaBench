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
struct thermal_cooling_device {int dummy; } ;
struct devfreq {int dummy; } ;

/* Variables and functions */
 struct thermal_cooling_device* of_devfreq_cooling_register (int /*<<< orphan*/ *,struct devfreq*) ; 

struct thermal_cooling_device *devfreq_cooling_register(struct devfreq *df)
{
	return of_devfreq_cooling_register(NULL, df);
}