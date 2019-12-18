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
struct tda8290_priv {int /*<<< orphan*/  i2c_props; } ;
struct dvb_frontend {struct tda8290_priv* analog_demod_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  tda8295_agc1_out (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda8295_agc2_out (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda8295_power (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  tda8295_set_easy_mode (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda8295_set_video_std (struct dvb_frontend*) ; 
 int /*<<< orphan*/  tuner_i2c_xfer_send (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static void tda8295_init_if(struct dvb_frontend *fe)
{
	struct tda8290_priv *priv = fe->analog_demod_priv;

	static unsigned char set_adc_ctl[]       = { 0x33, 0x14 };
	static unsigned char set_adc_ctl2[]      = { 0x34, 0x00 };
	static unsigned char set_pll_reg6[]      = { 0x3e, 0x63 };
	static unsigned char set_pll_reg0[]      = { 0x38, 0x23 };
	static unsigned char set_pll_reg7[]      = { 0x3f, 0x01 };
	static unsigned char set_pll_reg10[]     = { 0x42, 0x61 };
	static unsigned char set_gpio_reg0[]     = { 0x44, 0x0b };

	tda8295_power(fe, 1);

	tda8295_set_easy_mode(fe, 0);
	tda8295_set_video_std(fe);

	tuner_i2c_xfer_send(&priv->i2c_props, set_adc_ctl, 2);
	tuner_i2c_xfer_send(&priv->i2c_props, set_adc_ctl2, 2);
	tuner_i2c_xfer_send(&priv->i2c_props, set_pll_reg6, 2);
	tuner_i2c_xfer_send(&priv->i2c_props, set_pll_reg0, 2);
	tuner_i2c_xfer_send(&priv->i2c_props, set_pll_reg7, 2);
	tuner_i2c_xfer_send(&priv->i2c_props, set_pll_reg10, 2);
	tuner_i2c_xfer_send(&priv->i2c_props, set_gpio_reg0, 2);

	tda8295_agc1_out(fe, 0);
	tda8295_agc2_out(fe, 0);
}