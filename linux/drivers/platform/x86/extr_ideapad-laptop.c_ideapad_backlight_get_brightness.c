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
struct ideapad_private {TYPE_1__* adev; } ;
struct backlight_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  VPCCMD_R_BL ; 
 struct ideapad_private* bl_get_data (struct backlight_device*) ; 
 scalar_t__ read_ec_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int ideapad_backlight_get_brightness(struct backlight_device *blightdev)
{
	struct ideapad_private *priv = bl_get_data(blightdev);
	unsigned long now;

	if (!priv)
		return -EINVAL;

	if (read_ec_data(priv->adev->handle, VPCCMD_R_BL, &now))
		return -EIO;
	return now;
}