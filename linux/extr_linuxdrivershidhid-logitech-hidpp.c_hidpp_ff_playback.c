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
typedef  int /*<<< orphan*/  u8 ;
struct input_dev {TYPE_1__* ff; } ;
struct hidpp_ff_private_data {int dummy; } ;
struct TYPE_2__ {struct hidpp_ff_private_data* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HIDPP_FF_EFFECT_STATE_PLAY ; 
 int /*<<< orphan*/  HIDPP_FF_EFFECT_STATE_STOP ; 
 int /*<<< orphan*/  HIDPP_FF_SET_EFFECT_STATE ; 
 int /*<<< orphan*/  dbg_hid (char*,char*,int) ; 
 int hidpp_ff_queue_work (struct hidpp_ff_private_data*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hidpp_ff_playback(struct input_dev *dev, int effect_id, int value)
{
	struct hidpp_ff_private_data *data = dev->ff->private;
	u8 params[2];

	params[1] = value ? HIDPP_FF_EFFECT_STATE_PLAY : HIDPP_FF_EFFECT_STATE_STOP;

	dbg_hid("St%sing playback of effect %d.\n", value?"art":"opp", effect_id);

	return hidpp_ff_queue_work(data, effect_id, HIDPP_FF_SET_EFFECT_STATE, params, ARRAY_SIZE(params));
}