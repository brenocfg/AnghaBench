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
typedef  int u8 ;
typedef  int u16 ;
struct input_dev {TYPE_1__* ff; } ;
struct hidpp_ff_private_data {int dummy; } ;
struct TYPE_2__ {struct hidpp_ff_private_data* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int HIDPP_AUTOCENTER_PARAMS_LENGTH ; 
 int /*<<< orphan*/  HIDPP_FF_DOWNLOAD_EFFECT ; 
 int /*<<< orphan*/  HIDPP_FF_EFFECTID_AUTOCENTER ; 
 int HIDPP_FF_EFFECT_AUTOSTART ; 
 int HIDPP_FF_EFFECT_SPRING ; 
 int /*<<< orphan*/  dbg_hid (char*,int) ; 
 int /*<<< orphan*/  hidpp_ff_queue_work (struct hidpp_ff_private_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hidpp_ff_set_autocenter(struct input_dev *dev, u16 magnitude)
{
	struct hidpp_ff_private_data *data = dev->ff->private;
	u8 params[HIDPP_AUTOCENTER_PARAMS_LENGTH];

	dbg_hid("Setting autocenter to %d.\n", magnitude);

	/* start a standard spring effect */
	params[1] = HIDPP_FF_EFFECT_SPRING | HIDPP_FF_EFFECT_AUTOSTART;
	/* zero delay and duration */
	params[2] = params[3] = params[4] = params[5] = 0;
	/* set coeff to 25% of saturation */
	params[8] = params[14] = magnitude >> 11;
	params[9] = params[15] = (magnitude >> 3) & 255;
	params[6] = params[16] = magnitude >> 9;
	params[7] = params[17] = (magnitude >> 1) & 255;
	/* zero deadband and center */
	params[10] = params[11] = params[12] = params[13] = 0;

	hidpp_ff_queue_work(data, HIDPP_FF_EFFECTID_AUTOCENTER, HIDPP_FF_DOWNLOAD_EFFECT, params, ARRAY_SIZE(params));
}