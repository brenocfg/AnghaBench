#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct tuner_setup {unsigned int mode_mask; scalar_t__ type; int addr; int /*<<< orphan*/  tuner_callback; } ;
struct TYPE_3__ {scalar_t__ tuner_type; int tuner_addr; scalar_t__ has_analog; } ;
struct au0828_dev {int /*<<< orphan*/  v4l2_dev; TYPE_1__ board; int /*<<< orphan*/  i2c_adap; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ AU0828_VMUX_UNDEFINED ; 
 TYPE_2__ AUVI_INPUT (int /*<<< orphan*/ ) ; 
 scalar_t__ TUNER_ABSENT ; 
 unsigned int T_ANALOG_TV ; 
 int /*<<< orphan*/  au0828_tuner_callback ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  s_type_addr ; 
 int /*<<< orphan*/  tuner ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tuner_setup*) ; 
 struct v4l2_subdev* v4l2_i2c_new_subdev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 

void au0828_card_analog_fe_setup(struct au0828_dev *dev)
{
#ifdef CONFIG_VIDEO_AU0828_V4L2
	struct tuner_setup tun_setup;
	struct v4l2_subdev *sd;
	unsigned int mode_mask = T_ANALOG_TV;

	if (AUVI_INPUT(0).type != AU0828_VMUX_UNDEFINED) {
		/* Load the analog demodulator driver (note this would need to
		   be abstracted out if we ever need to support a different
		   demod) */
		sd = v4l2_i2c_new_subdev(&dev->v4l2_dev, &dev->i2c_adap,
				"au8522", 0x8e >> 1, NULL);
		if (sd == NULL)
			pr_err("analog subdev registration failed\n");
	}

	/* Setup tuners */
	if (dev->board.tuner_type != TUNER_ABSENT && dev->board.has_analog) {
		/* Load the tuner module, which does the attach */
		sd = v4l2_i2c_new_subdev(&dev->v4l2_dev, &dev->i2c_adap,
				"tuner", dev->board.tuner_addr, NULL);
		if (sd == NULL)
			pr_err("tuner subdev registration fail\n");

		tun_setup.mode_mask      = mode_mask;
		tun_setup.type           = dev->board.tuner_type;
		tun_setup.addr           = dev->board.tuner_addr;
		tun_setup.tuner_callback = au0828_tuner_callback;
		v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_type_addr,
				     &tun_setup);
	}
#endif
}