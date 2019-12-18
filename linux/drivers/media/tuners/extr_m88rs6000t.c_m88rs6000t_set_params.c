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
typedef  int u32 ;
struct m88rs6000t_dev {TYPE_1__* client; int /*<<< orphan*/  regmap; } ;
struct dtv_frontend_properties {int frequency; int symbol_rate; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct m88rs6000t_dev* tuner_priv; } ;
typedef  int s32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int m88rs6000t_set_bb (struct m88rs6000t_dev*,int,int) ; 
 int m88rs6000t_set_demod_mclk (struct dvb_frontend*) ; 
 int m88rs6000t_set_pll_freq (struct m88rs6000t_dev*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int m88rs6000t_set_params(struct dvb_frontend *fe)
{
	struct m88rs6000t_dev *dev = fe->tuner_priv;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	int ret;
	s32 lpf_offset_KHz;
	u32 realFreq, freq_MHz;

	dev_dbg(&dev->client->dev,
			"frequency=%d symbol_rate=%d\n",
			c->frequency, c->symbol_rate);

	if (c->symbol_rate < 5000000)
		lpf_offset_KHz = 3000;
	else
		lpf_offset_KHz = 0;

	realFreq = c->frequency + lpf_offset_KHz;
	/* set tuner pll.*/
	freq_MHz = (realFreq + 500) / 1000;
	ret = m88rs6000t_set_pll_freq(dev, freq_MHz);
	if (ret)
		goto err;
	ret = m88rs6000t_set_bb(dev, c->symbol_rate / 1000, lpf_offset_KHz);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x00, 0x01);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x00, 0x00);
	if (ret)
		goto err;
	/* set demod mlck */
	ret = m88rs6000t_set_demod_mclk(fe);
err:
	if (ret)
		dev_dbg(&dev->client->dev, "failed=%d\n", ret);
	return ret;
}