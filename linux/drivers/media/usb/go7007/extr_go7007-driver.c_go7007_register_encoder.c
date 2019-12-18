#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tuner_setup {scalar_t__ type; int /*<<< orphan*/  mode_mask; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  release; } ;
struct go7007 {int i2c_adapter_online; scalar_t__ board_id; scalar_t__ tuner_type; int audio_enabled; TYPE_1__* board_info; scalar_t__ channel_number; int /*<<< orphan*/  sd_video; TYPE_2__ v4l2_dev; int /*<<< orphan*/  i2c_adapter; int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/ * i2c_devs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_UNSET ; 
 scalar_t__ GO7007_BOARDID_ADLINK_MPG24 ; 
 scalar_t__ GO7007_BOARDID_ADS_USBAV_709 ; 
 int GO7007_BOARD_HAS_AUDIO ; 
 int GO7007_BOARD_USE_ONBOARD_I2C ; 
 int /*<<< orphan*/  T_ANALOG_TV ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int go7007_i2c_init (struct go7007*) ; 
 int go7007_init_encoder (struct go7007*) ; 
 int /*<<< orphan*/  go7007_remove ; 
 int /*<<< orphan*/  go7007_snd_init (struct go7007*) ; 
 int go7007_v4l2_ctrl_init (struct go7007*) ; 
 int go7007_v4l2_init (struct go7007*) ; 
 int /*<<< orphan*/  go7007_write_addr (struct go7007*,int,int) ; 
 int /*<<< orphan*/  init_i2c_module (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_routing ; 
 int /*<<< orphan*/  s_type_addr ; 
 int /*<<< orphan*/  tuner ; 
 int /*<<< orphan*/  v4l2_device_call_all (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tuner_setup*) ; 
 int v4l2_device_register (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  video ; 

int go7007_register_encoder(struct go7007 *go, unsigned num_i2c_devs)
{
	int i, ret;

	dev_info(go->dev, "go7007: registering new %s\n", go->name);

	go->v4l2_dev.release = go7007_remove;
	ret = v4l2_device_register(go->dev, &go->v4l2_dev);
	if (ret < 0)
		return ret;

	mutex_lock(&go->hw_lock);
	ret = go7007_init_encoder(go);
	mutex_unlock(&go->hw_lock);
	if (ret < 0)
		return ret;

	ret = go7007_v4l2_ctrl_init(go);
	if (ret < 0)
		return ret;

	if (!go->i2c_adapter_online &&
			go->board_info->flags & GO7007_BOARD_USE_ONBOARD_I2C) {
		ret = go7007_i2c_init(go);
		if (ret < 0)
			return ret;
		go->i2c_adapter_online = 1;
	}
	if (go->i2c_adapter_online) {
		if (go->board_id == GO7007_BOARDID_ADS_USBAV_709) {
			/* Reset the TW9906 */
			go7007_write_addr(go, 0x3c82, 0x0009);
			msleep(50);
			go7007_write_addr(go, 0x3c82, 0x000d);
		}
		for (i = 0; i < num_i2c_devs; ++i)
			init_i2c_module(&go->i2c_adapter, &go->board_info->i2c_devs[i]);

		if (go->tuner_type >= 0) {
			struct tuner_setup setup = {
				.addr = ADDR_UNSET,
				.type = go->tuner_type,
				.mode_mask = T_ANALOG_TV,
			};

			v4l2_device_call_all(&go->v4l2_dev, 0, tuner,
				s_type_addr, &setup);
		}
		if (go->board_id == GO7007_BOARDID_ADLINK_MPG24)
			v4l2_subdev_call(go->sd_video, video, s_routing,
					0, 0, go->channel_number + 1);
	}

	ret = go7007_v4l2_init(go);
	if (ret < 0)
		return ret;

	if (go->board_info->flags & GO7007_BOARD_HAS_AUDIO) {
		go->audio_enabled = 1;
		go7007_snd_init(go);
	}
	return 0;
}