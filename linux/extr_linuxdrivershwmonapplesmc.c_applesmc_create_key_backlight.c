#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  has_key_backlight; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  applesmc_backlight ; 
 int /*<<< orphan*/  applesmc_led_wq ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int led_classdev_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* pdev ; 
 TYPE_1__ smcreg ; 

__attribute__((used)) static int applesmc_create_key_backlight(void)
{
	if (!smcreg.has_key_backlight)
		return 0;
	applesmc_led_wq = create_singlethread_workqueue("applesmc-led");
	if (!applesmc_led_wq)
		return -ENOMEM;
	return led_classdev_register(&pdev->dev, &applesmc_backlight);
}