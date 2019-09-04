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
struct s6e3ha2 {struct backlight_device* bl_dev; } ;
struct TYPE_2__ {unsigned int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (unsigned char*) ; 
 unsigned int S6E3HA2_MAX_BRIGHTNESS ; 
 int /*<<< orphan*/  S6E3HA2_VINT_STATUS_MAX ; 
 int s6e3ha2_dcs_write (struct s6e3ha2*,unsigned char*,int /*<<< orphan*/ ) ; 
 int* vint_table ; 

__attribute__((used)) static int s6e3ha2_set_vint(struct s6e3ha2 *ctx)
{
	struct backlight_device *bl_dev = ctx->bl_dev;
	unsigned int brightness = bl_dev->props.brightness;
	unsigned char data[] = { 0xf4, 0x8b,
			vint_table[brightness * (S6E3HA2_VINT_STATUS_MAX - 1) /
			S6E3HA2_MAX_BRIGHTNESS] };

	return s6e3ha2_dcs_write(ctx, data, ARRAY_SIZE(data));
}