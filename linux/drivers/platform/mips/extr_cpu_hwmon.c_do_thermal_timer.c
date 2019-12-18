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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int CPU_THERMAL_THRESHOLD ; 
 int loongson3_cpu_temp (int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int nr_packages ; 
 int /*<<< orphan*/  orderly_poweroff (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_work ; 

__attribute__((used)) static void do_thermal_timer(struct work_struct *work)
{
	int i, value, temp_max = 0;

	for (i=0; i<nr_packages; i++) {
		value = loongson3_cpu_temp(i);
		if (value > temp_max)
			temp_max = value;
	}

	if (temp_max <= CPU_THERMAL_THRESHOLD)
		schedule_delayed_work(&thermal_work, msecs_to_jiffies(5000));
	else
		orderly_poweroff(true);
}