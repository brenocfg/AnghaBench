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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C64XX_GPB (int) ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int hmt_bl_init(struct device *dev)
{
	int ret;

	ret = gpio_request(S3C64XX_GPB(4), "lcd backlight enable");
	if (!ret)
		ret = gpio_direction_output(S3C64XX_GPB(4), 0);

	return ret;
}