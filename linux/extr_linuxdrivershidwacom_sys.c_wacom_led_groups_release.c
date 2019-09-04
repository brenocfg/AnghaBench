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
struct TYPE_2__ {scalar_t__ count; int /*<<< orphan*/ * groups; } ;
struct wacom {TYPE_1__ led; } ;

/* Variables and functions */

__attribute__((used)) static void wacom_led_groups_release(void *data)
{
	struct wacom *wacom = data;

	wacom->led.groups = NULL;
	wacom->led.count = 0;
}