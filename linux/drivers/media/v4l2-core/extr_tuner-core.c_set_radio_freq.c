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
struct analog_demod_ops {int /*<<< orphan*/  (* set_params ) (TYPE_2__*,struct analog_parameters*) ;} ;
struct TYPE_3__ {struct analog_demod_ops analog_ops; } ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct tuner {scalar_t__ type; unsigned int radio_freq; int standby; int /*<<< orphan*/  audmode; TYPE_2__ fe; int /*<<< orphan*/  std; int /*<<< orphan*/  mode; } ;
struct i2c_client {int dummy; } ;
struct analog_parameters {unsigned int frequency; int /*<<< orphan*/  audmode; int /*<<< orphan*/  std; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ UNSET ; 
 int /*<<< orphan*/  dprintk (char*,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int* radio_range ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct analog_parameters*) ; 
 struct tuner* to_tuner (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_radio_freq(struct i2c_client *c, unsigned int freq)
{
	struct tuner *t = to_tuner(i2c_get_clientdata(c));
	struct analog_demod_ops *analog_ops = &t->fe.ops.analog_ops;

	struct analog_parameters params = {
		.mode      = t->mode,
		.audmode   = t->audmode,
		.std       = t->std
	};

	if (t->type == UNSET) {
		pr_warn("tuner type not set\n");
		return;
	}
	if (NULL == analog_ops->set_params) {
		pr_warn("tuner has no way to set radio frequency\n");
		return;
	}
	if (freq < radio_range[0] * 16000 || freq > radio_range[1] * 16000) {
		dprintk("radio freq (%d.%02d) out of range (%d-%d)\n",
			   freq / 16000, freq % 16000 * 100 / 16000,
			   radio_range[0], radio_range[1]);
		/* V4L2 spec: if the freq is not possible then the closest
		   possible value should be selected */
		if (freq < radio_range[0] * 16000)
			freq = radio_range[0] * 16000;
		else
			freq = radio_range[1] * 16000;
	}
	params.frequency = freq;
	dprintk("radio freq set to %d.%02d\n",
			freq / 16000, freq % 16000 * 100 / 16000);
	t->radio_freq = freq;
	t->standby = false;

	analog_ops->set_params(&t->fe, &params);
	/*
	 * The tuner driver might decide to change the audmode if it only
	 * supports stereo, so update t->audmode.
	 */
	t->audmode = params.audmode;
}