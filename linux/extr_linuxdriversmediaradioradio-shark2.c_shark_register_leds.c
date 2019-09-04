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
struct shark_device {int /*<<< orphan*/  v4l2_dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int shark_register_leds(struct shark_device *shark, struct device *dev)
{
	v4l2_warn(&shark->v4l2_dev,
		  "CONFIG_LEDS_CLASS not enabled, LED support disabled\n");
	return 0;
}