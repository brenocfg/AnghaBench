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
struct v4l2_subdev {int dummy; } ;
struct adv7183 {int /*<<< orphan*/  oe_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 struct adv7183* to_adv7183 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int adv7183_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct adv7183 *decoder = to_adv7183(sd);

	if (enable)
		gpio_set_value(decoder->oe_pin, 0);
	else
		gpio_set_value(decoder->oe_pin, 1);
	udelay(1);
	return 0;
}