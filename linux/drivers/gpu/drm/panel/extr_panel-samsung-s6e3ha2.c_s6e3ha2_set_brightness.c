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
struct s6e3ha2 {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned int brightness; unsigned int max_brightness; scalar_t__ power; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ FB_BLANK_NORMAL ; 
 unsigned int S6E3HA2_MIN_BRIGHTNESS ; 
 struct s6e3ha2* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  s6e3ha2_aor_control (struct s6e3ha2*) ; 
 int /*<<< orphan*/  s6e3ha2_call_write_func (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s6e3ha2_set_vint (struct s6e3ha2*) ; 
 int /*<<< orphan*/  s6e3ha2_test_key_off_f0 (struct s6e3ha2*) ; 
 int /*<<< orphan*/  s6e3ha2_test_key_on_f0 (struct s6e3ha2*) ; 
 int /*<<< orphan*/  s6e3ha2_update_gamma (struct s6e3ha2*,unsigned int) ; 

__attribute__((used)) static int s6e3ha2_set_brightness(struct backlight_device *bl_dev)
{
	struct s6e3ha2 *ctx = bl_get_data(bl_dev);
	unsigned int brightness = bl_dev->props.brightness;
	int ret;

	if (brightness < S6E3HA2_MIN_BRIGHTNESS ||
		brightness > bl_dev->props.max_brightness) {
		dev_err(ctx->dev, "Invalid brightness: %u\n", brightness);
		return -EINVAL;
	}

	if (bl_dev->props.power > FB_BLANK_NORMAL)
		return -EPERM;

	s6e3ha2_call_write_func(ret, s6e3ha2_test_key_on_f0(ctx));
	s6e3ha2_call_write_func(ret, s6e3ha2_update_gamma(ctx, brightness));
	s6e3ha2_call_write_func(ret, s6e3ha2_aor_control(ctx));
	s6e3ha2_call_write_func(ret, s6e3ha2_set_vint(ctx));
	s6e3ha2_call_write_func(ret, s6e3ha2_test_key_off_f0(ctx));

	return 0;
}