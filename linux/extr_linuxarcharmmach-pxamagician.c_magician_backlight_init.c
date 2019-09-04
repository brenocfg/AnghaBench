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
 int /*<<< orphan*/  ARRAY_AND_SIZE (int /*<<< orphan*/ ) ; 
 int gpio_request_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  magician_bl_gpios ; 

__attribute__((used)) static int magician_backlight_init(struct device *dev)
{
	return gpio_request_array(ARRAY_AND_SIZE(magician_bl_gpios));
}