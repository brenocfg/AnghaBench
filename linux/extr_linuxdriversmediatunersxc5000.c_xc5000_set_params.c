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
struct xc5000_priv {int mode; } ;
struct dvb_frontend {struct xc5000_priv* tuner_priv; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_TUNER_ANALOG_TV 130 
#define  V4L2_TUNER_DIGITAL_TV 129 
#define  V4L2_TUNER_RADIO 128 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int xc5000_set_radio_freq (struct dvb_frontend*) ; 
 int xc5000_set_tv_freq (struct dvb_frontend*) ; 
 int xc5000_tune_digital (struct dvb_frontend*) ; 
 scalar_t__ xc_load_fw_and_init_tuner (struct dvb_frontend*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xc5000_set_params(struct dvb_frontend *fe)
{
	struct xc5000_priv *priv = fe->tuner_priv;

	if (xc_load_fw_and_init_tuner(fe, 0) != 0) {
		dprintk(1, "Unable to load firmware and init tuner\n");
		return -EINVAL;
	}

	switch (priv->mode) {
	case V4L2_TUNER_RADIO:
		return xc5000_set_radio_freq(fe);
	case V4L2_TUNER_ANALOG_TV:
		return xc5000_set_tv_freq(fe);
	case V4L2_TUNER_DIGITAL_TV:
		return xc5000_tune_digital(fe);
	}

	return 0;
}