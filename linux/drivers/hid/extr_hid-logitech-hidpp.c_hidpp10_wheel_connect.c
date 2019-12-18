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
struct hidpp_device {int dummy; } ;

/* Variables and functions */
 int HIDPP_ENABLE_HWHEEL_REPORT ; 
 int HIDPP_ENABLE_WHEEL_REPORT ; 
 int /*<<< orphan*/  HIDPP_REG_ENABLE_REPORTS ; 
 int hidpp10_set_register (struct hidpp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int hidpp10_wheel_connect(struct hidpp_device *hidpp)
{
	return hidpp10_set_register(hidpp, HIDPP_REG_ENABLE_REPORTS, 0,
			HIDPP_ENABLE_WHEEL_REPORT | HIDPP_ENABLE_HWHEEL_REPORT,
			HIDPP_ENABLE_WHEEL_REPORT | HIDPP_ENABLE_HWHEEL_REPORT);
}