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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int state; scalar_t__ power; scalar_t__ brightness; } ;
struct backlight_device {TYPE_1__ props; } ;
struct arcxcnn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCXCNN_CMD ; 
 int /*<<< orphan*/  ARCXCNN_CMD_STDBY ; 
 int BL_CORE_FBBLANK ; 
 int BL_CORE_SUSPENDED ; 
 int arcxcnn_set_brightness (struct arcxcnn*,scalar_t__) ; 
 int arcxcnn_update_field (struct arcxcnn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct arcxcnn* bl_get_data (struct backlight_device*) ; 

__attribute__((used)) static int arcxcnn_bl_update_status(struct backlight_device *bl)
{
	struct arcxcnn *lp = bl_get_data(bl);
	u32 brightness = bl->props.brightness;
	int ret;

	if (bl->props.state & (BL_CORE_SUSPENDED | BL_CORE_FBBLANK))
		brightness = 0;

	ret = arcxcnn_set_brightness(lp, brightness);
	if (ret)
		return ret;

	/* set power-on/off/save modes */
	return arcxcnn_update_field(lp, ARCXCNN_CMD, ARCXCNN_CMD_STDBY,
		(bl->props.power == 0) ? 0 : ARCXCNN_CMD_STDBY);
}