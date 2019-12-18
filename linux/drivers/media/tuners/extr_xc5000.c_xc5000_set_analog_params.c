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
struct TYPE_2__ {int /*<<< orphan*/ * adap; } ;
struct xc5000_priv {int mode; TYPE_1__ i2c_props; } ;
struct dvb_frontend {struct xc5000_priv* tuner_priv; } ;
struct analog_parameters {int mode; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_TUNER_ANALOG_TV 129 
#define  V4L2_TUNER_RADIO 128 
 int xc5000_config_radio (struct dvb_frontend*,struct analog_parameters*) ; 
 int /*<<< orphan*/  xc5000_config_tv (struct dvb_frontend*,struct analog_parameters*) ; 
 int xc5000_set_params (struct dvb_frontend*) ; 

__attribute__((used)) static int xc5000_set_analog_params(struct dvb_frontend *fe,
			     struct analog_parameters *params)
{
	struct xc5000_priv *priv = fe->tuner_priv;
	int ret;

	if (priv->i2c_props.adap == NULL)
		return -EINVAL;

	switch (params->mode) {
	case V4L2_TUNER_RADIO:
		ret = xc5000_config_radio(fe, params);
		if (ret)
			return ret;
		break;
	case V4L2_TUNER_ANALOG_TV:
		xc5000_config_tv(fe, params);
		break;
	default:
		break;
	}
	priv->mode = params->mode;

	return xc5000_set_params(fe);
}