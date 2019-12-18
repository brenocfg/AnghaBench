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
struct ips_driver {int ctv2_avg_temp; int ctv1_avg_temp; int cpu_avg_power; int core_power_limit; int /*<<< orphan*/  dev; int /*<<< orphan*/  turbo_status_lock; TYPE_1__* limits; } ;
struct TYPE_2__ {int core_temp_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool cpu_exceeded(struct ips_driver *ips, int cpu)
{
	unsigned long flags;
	int avg;
	bool ret = false;

	spin_lock_irqsave(&ips->turbo_status_lock, flags);
	avg = cpu ? ips->ctv2_avg_temp : ips->ctv1_avg_temp;
	if (avg > (ips->limits->core_temp_limit * 100))
		ret = true;
	if (ips->cpu_avg_power > ips->core_power_limit * 100)
		ret = true;
	spin_unlock_irqrestore(&ips->turbo_status_lock, flags);

	if (ret)
		dev_info(ips->dev, "CPU power or thermal limit exceeded\n");

	return ret;
}