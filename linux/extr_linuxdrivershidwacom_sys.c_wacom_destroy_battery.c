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
struct TYPE_4__ {int /*<<< orphan*/ * battery; int /*<<< orphan*/  bat_desc; } ;
struct wacom {TYPE_2__ battery; TYPE_1__* hdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devres_release_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wacom_destroy_battery(struct wacom *wacom)
{
	if (wacom->battery.battery) {
		devres_release_group(&wacom->hdev->dev,
				     &wacom->battery.bat_desc);
		wacom->battery.battery = NULL;
	}
}