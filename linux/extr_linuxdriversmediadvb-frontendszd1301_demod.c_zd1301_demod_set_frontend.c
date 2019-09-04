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
typedef  int u8 ;
typedef  int u32 ;
struct zd1301_demod_dev {struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int (* set_params ) (struct dvb_frontend*) ;int (* get_if_frequency ) (struct dvb_frontend*,int*) ;} ;
struct TYPE_4__ {TYPE_1__ tuner_ops; } ;
struct dtv_frontend_properties {int bandwidth_hz; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {TYPE_2__ ops; struct dtv_frontend_properties dtv_property_cache; struct zd1301_demod_dev* demodulator_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int stub1 (struct dvb_frontend*) ; 
 int stub2 (struct dvb_frontend*,int*) ; 
 int zd1301_demod_wreg (struct zd1301_demod_dev*,int,int) ; 

__attribute__((used)) static int zd1301_demod_set_frontend(struct dvb_frontend *fe)
{
	struct zd1301_demod_dev *dev = fe->demodulator_priv;
	struct platform_device *pdev = dev->pdev;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	int ret;
	u32 if_frequency;
	u8 r6a50_val;

	dev_dbg(&pdev->dev, "frequency=%u bandwidth_hz=%u\n",
		c->frequency, c->bandwidth_hz);

	/* Program tuner */
	if (fe->ops.tuner_ops.set_params &&
	    fe->ops.tuner_ops.get_if_frequency) {
		ret = fe->ops.tuner_ops.set_params(fe);
		if (ret)
			goto err;
		ret = fe->ops.tuner_ops.get_if_frequency(fe, &if_frequency);
		if (ret)
			goto err;
	} else {
		ret = -EINVAL;
		goto err;
	}

	dev_dbg(&pdev->dev, "if_frequency=%u\n", if_frequency);
	if (if_frequency != 36150000) {
		ret = -EINVAL;
		goto err;
	}

	switch (c->bandwidth_hz) {
	case 6000000:
		r6a50_val = 0x78;
		break;
	case 7000000:
		r6a50_val = 0x68;
		break;
	case 8000000:
		r6a50_val = 0x58;
		break;
	default:
		ret = -EINVAL;
		goto err;
	}

	ret = zd1301_demod_wreg(dev, 0x6a60, 0x11);
	if (ret)
		goto err;
	ret = zd1301_demod_wreg(dev, 0x6a47, 0x46);
	if (ret)
		goto err;
	ret = zd1301_demod_wreg(dev, 0x6a48, 0x46);
	if (ret)
		goto err;
	ret = zd1301_demod_wreg(dev, 0x6a4a, 0x15);
	if (ret)
		goto err;
	ret = zd1301_demod_wreg(dev, 0x6a4b, 0x63);
	if (ret)
		goto err;
	ret = zd1301_demod_wreg(dev, 0x6a5b, 0x99);
	if (ret)
		goto err;
	ret = zd1301_demod_wreg(dev, 0x6a3b, 0x10);
	if (ret)
		goto err;
	ret = zd1301_demod_wreg(dev, 0x6806, 0x01);
	if (ret)
		goto err;
	ret = zd1301_demod_wreg(dev, 0x6a41, 0x08);
	if (ret)
		goto err;
	ret = zd1301_demod_wreg(dev, 0x6a42, 0x46);
	if (ret)
		goto err;
	ret = zd1301_demod_wreg(dev, 0x6a44, 0x14);
	if (ret)
		goto err;
	ret = zd1301_demod_wreg(dev, 0x6a45, 0x67);
	if (ret)
		goto err;
	ret = zd1301_demod_wreg(dev, 0x6a38, 0x00);
	if (ret)
		goto err;
	ret = zd1301_demod_wreg(dev, 0x6a4c, 0x52);
	if (ret)
		goto err;
	ret = zd1301_demod_wreg(dev, 0x6a49, 0x2a);
	if (ret)
		goto err;
	ret = zd1301_demod_wreg(dev, 0x6840, 0x2e);
	if (ret)
		goto err;
	ret = zd1301_demod_wreg(dev, 0x6a50, r6a50_val);
	if (ret)
		goto err;
	ret = zd1301_demod_wreg(dev, 0x6a38, 0x07);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&pdev->dev, "failed=%d\n", ret);
	return ret;
}