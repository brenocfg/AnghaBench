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
struct s6e63j0x03 {struct backlight_device* bl_dev; } ;
struct TYPE_2__ {unsigned int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAMMA_CMD_CNT ; 
 int /*<<< orphan*/ * gamma_tbl ; 
 int s6e63j0x03_apply_mtp_key (struct s6e63j0x03*,int) ; 
 int s6e63j0x03_dcs_write_seq (struct s6e63j0x03*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int s6e63j0x03_get_brightness_index (unsigned int) ; 

__attribute__((used)) static int s6e63j0x03_update_gamma(struct s6e63j0x03 *ctx,
					unsigned int brightness)
{
	struct backlight_device *bl_dev = ctx->bl_dev;
	unsigned int index = s6e63j0x03_get_brightness_index(brightness);
	int ret;

	ret = s6e63j0x03_apply_mtp_key(ctx, true);
	if (ret < 0)
		return ret;

	ret = s6e63j0x03_dcs_write_seq(ctx, gamma_tbl[index], GAMMA_CMD_CNT);
	if (ret < 0)
		return ret;

	ret = s6e63j0x03_apply_mtp_key(ctx, false);
	if (ret < 0)
		return ret;

	bl_dev->props.brightness = brightness;

	return 0;
}