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
struct abx500_temp {TYPE_1__* pdev; struct ab8500_temp* plat_data; } ;
struct ab8500_temp {int /*<<< orphan*/  power_off_work; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DEFAULT_POWER_OFF_DELAY ; 
 int HZ ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ab8500_temp_irq_handler(int irq, struct abx500_temp *data)
{
	struct ab8500_temp *ab8500_data = data->plat_data;

	dev_warn(&data->pdev->dev, "Power off in %d s\n",
		 DEFAULT_POWER_OFF_DELAY / HZ);

	schedule_delayed_work(&ab8500_data->power_off_work,
		DEFAULT_POWER_OFF_DELAY);
	return 0;
}