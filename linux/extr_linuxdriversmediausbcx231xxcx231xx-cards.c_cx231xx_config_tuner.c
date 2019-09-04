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
struct v4l2_frequency {int frequency; int /*<<< orphan*/  type; scalar_t__ tuner; } ;
struct tuner_setup {int mode_mask; scalar_t__ type; int /*<<< orphan*/  tuner_callback; int /*<<< orphan*/  addr; } ;
struct cx231xx {scalar_t__ tuner_type; int ctl_freq; int /*<<< orphan*/  tuner_addr; } ;

/* Variables and functions */
 scalar_t__ TUNER_ABSENT ; 
 int T_ANALOG_TV ; 
 int T_RADIO ; 
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 
 int /*<<< orphan*/  call_all (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 
 int /*<<< orphan*/  cx231xx_tuner_callback ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  s_type_addr ; 
 int /*<<< orphan*/  tuner ; 
 int /*<<< orphan*/  tuner_call (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tuner_setup*) ; 

__attribute__((used)) static void cx231xx_config_tuner(struct cx231xx *dev)
{
	struct tuner_setup tun_setup;
	struct v4l2_frequency f;

	if (dev->tuner_type == TUNER_ABSENT)
		return;

	tun_setup.mode_mask = T_ANALOG_TV | T_RADIO;
	tun_setup.type = dev->tuner_type;
	tun_setup.addr = dev->tuner_addr;
	tun_setup.tuner_callback = cx231xx_tuner_callback;

	tuner_call(dev, tuner, s_type_addr, &tun_setup);

#if 0
	if (tun_setup.type == TUNER_XC5000) {
		static struct xc2028_ctrl ctrl = {
			.fname = XC5000_DEFAULT_FIRMWARE,
			.max_len = 64,
			.demod = 0;
		};
		struct v4l2_priv_tun_config cfg = {
			.tuner = dev->tuner_type,
			.priv = &ctrl,
		};
		tuner_call(dev, tuner, s_config, &cfg);
	}
#endif
	/* configure tuner */
	f.tuner = 0;
	f.type = V4L2_TUNER_ANALOG_TV;
	f.frequency = 9076;	/* just a magic number */
	dev->ctl_freq = f.frequency;
	call_all(dev, tuner, s_frequency, &f);

}