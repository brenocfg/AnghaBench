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
struct tuner {scalar_t__ mode; unsigned int radio_freq; unsigned int tv_freq; int /*<<< orphan*/  sd; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  set_radio_freq (struct i2c_client*,unsigned int) ; 
 int /*<<< orphan*/  set_tv_freq (struct i2c_client*,unsigned int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_freq(struct tuner *t, unsigned int freq)
{
	struct i2c_client *client = v4l2_get_subdevdata(&t->sd);

	if (t->mode == V4L2_TUNER_RADIO) {
		if (!freq)
			freq = t->radio_freq;
		set_radio_freq(client, freq);
	} else {
		if (!freq)
			freq = t->tv_freq;
		set_tv_freq(client, freq);
	}
}