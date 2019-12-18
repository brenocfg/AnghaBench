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
typedef  enum s3c2410_udc_cmd_e { ____Placeholder_s3c2410_udc_cmd_e } s3c2410_udc_cmd_e ;
struct TYPE_2__ {int pullup_pin_inverted; int /*<<< orphan*/  pullup_pin; int /*<<< orphan*/  (* udc_command ) (int) ;} ;

/* Variables and functions */
#define  S3C2410_UDC_P_DISABLE 129 
#define  S3C2410_UDC_P_ENABLE 128 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 TYPE_1__* udc_info ; 

__attribute__((used)) static void s3c2410_udc_command(enum s3c2410_udc_cmd_e cmd)
{
	if (!udc_info)
		return;

	if (udc_info->udc_command) {
		udc_info->udc_command(cmd);
	} else if (gpio_is_valid(udc_info->pullup_pin)) {
		int value;

		switch (cmd) {
		case S3C2410_UDC_P_ENABLE:
			value = 1;
			break;
		case S3C2410_UDC_P_DISABLE:
			value = 0;
			break;
		default:
			return;
		}
		value ^= udc_info->pullup_pin_inverted;

		gpio_set_value(udc_info->pullup_pin, value);
	}
}