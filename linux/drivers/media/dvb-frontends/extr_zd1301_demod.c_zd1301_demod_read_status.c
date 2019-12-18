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
typedef  int u8 ;
struct zd1301_demod_dev {scalar_t__ gain; struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct zd1301_demod_dev* demodulator_priv; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ zd1301_demod_gain ; 
 int zd1301_demod_rreg (struct zd1301_demod_dev*,int,int*) ; 
 int zd1301_demod_wreg (struct zd1301_demod_dev*,int,scalar_t__) ; 

__attribute__((used)) static int zd1301_demod_read_status(struct dvb_frontend *fe,
				    enum fe_status *status)
{
	struct zd1301_demod_dev *dev = fe->demodulator_priv;
	struct platform_device *pdev = dev->pdev;
	int ret;
	u8 u8tmp;

	ret = zd1301_demod_rreg(dev, 0x6a24, &u8tmp);
	if (ret)
		goto err;
	if (u8tmp > 0x00 && u8tmp < 0x20)
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_VITERBI |
			  FE_HAS_SYNC | FE_HAS_LOCK;
	else
		*status = 0;

	dev_dbg(&pdev->dev, "lock byte=%02x\n", u8tmp);

	/*
	 * Interesting registers here are:
	 * 0x6a05: get some gain value
	 * 0x6a06: get about same gain value than set to 0x6a43
	 * 0x6a07: get some gain value
	 * 0x6a43: set gain value by driver
	 * 0x6a24: get demod lock bits (FSM stage?)
	 *
	 * Driver should implement some kind of algorithm to calculate suitable
	 * value for register 0x6a43, based likely values from register 0x6a05
	 * and 0x6a07. Looks like gain register 0x6a43 value could be from
	 * range 0x00 - 0x70.
	 */

	if (dev->gain != zd1301_demod_gain) {
		dev->gain = zd1301_demod_gain;

		ret = zd1301_demod_wreg(dev, 0x6a43, dev->gain);
		if (ret)
			goto err;
	}

	return 0;
err:
	dev_dbg(&pdev->dev, "failed=%d\n", ret);
	return ret;
}