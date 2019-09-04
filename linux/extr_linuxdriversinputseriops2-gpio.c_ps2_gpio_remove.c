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
struct ps2_gpio_data {int /*<<< orphan*/  serio; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct ps2_gpio_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  serio_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ps2_gpio_remove(struct platform_device *pdev)
{
	struct ps2_gpio_data *drvdata = platform_get_drvdata(pdev);

	serio_unregister_port(drvdata->serio);
	return 0;
}