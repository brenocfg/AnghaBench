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
typedef  int u32 ;
struct mc44s803_priv {TYPE_1__* cfg; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {TYPE_2__ ops; struct mc44s803_priv* tuner_priv; } ;
struct TYPE_3__ {int dig_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  MC44S803_ADDR ; 
 int /*<<< orphan*/  MC44S803_AGC_AN_DIG ; 
 int /*<<< orphan*/  MC44S803_AGC_READ_EN ; 
 int /*<<< orphan*/  MC44S803_AT1 ; 
 int /*<<< orphan*/  MC44S803_AT2 ; 
 int /*<<< orphan*/  MC44S803_CIRCADJ_RES ; 
 int /*<<< orphan*/  MC44S803_CLIF ; 
 int /*<<< orphan*/  MC44S803_CLRF ; 
 int /*<<< orphan*/  MC44S803_G1 ; 
 int /*<<< orphan*/  MC44S803_G3 ; 
 int /*<<< orphan*/  MC44S803_G6 ; 
 int /*<<< orphan*/  MC44S803_LNA0 ; 
 int /*<<< orphan*/  MC44S803_LP ; 
 int /*<<< orphan*/  MC44S803_MIXER_RES ; 
 int /*<<< orphan*/  MC44S803_OSCSEL ; 
 int /*<<< orphan*/  MC44S803_POWER ; 
 int /*<<< orphan*/  MC44S803_REFOSC ; 
 int MC44S803_REG_CIRCADJ ; 
 int MC44S803_REG_DIGTUNE ; 
 int MC44S803_REG_LNAAGC ; 
 int MC44S803_REG_MIXER ; 
 int MC44S803_REG_POWER ; 
 int MC44S803_REG_REFOSC ; 
 int MC44S803_REG_RESET ; 
 int MC44S803_REG_SM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MC44S803_RS ; 
 int /*<<< orphan*/  MC44S803_S1 ; 
 int /*<<< orphan*/  MC44S803_TRI_STATE ; 
 int /*<<< orphan*/  MC44S803_XOD ; 
 int mc44s803_writereg (struct mc44s803_priv*,int) ; 
 int /*<<< orphan*/  mc_printk (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub3 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int mc44s803_init(struct dvb_frontend *fe)
{
	struct mc44s803_priv *priv = fe->tuner_priv;
	u32 val;
	int err;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

/* Reset chip */
	val = MC44S803_REG_SM(MC44S803_REG_RESET, MC44S803_ADDR) |
	      MC44S803_REG_SM(1, MC44S803_RS);

	err = mc44s803_writereg(priv, val);
	if (err)
		goto exit;

	val = MC44S803_REG_SM(MC44S803_REG_RESET, MC44S803_ADDR);

	err = mc44s803_writereg(priv, val);
	if (err)
		goto exit;

/* Power Up and Start Osc */

	val = MC44S803_REG_SM(MC44S803_REG_REFOSC, MC44S803_ADDR) |
	      MC44S803_REG_SM(0xC0, MC44S803_REFOSC) |
	      MC44S803_REG_SM(1, MC44S803_OSCSEL);

	err = mc44s803_writereg(priv, val);
	if (err)
		goto exit;

	val = MC44S803_REG_SM(MC44S803_REG_POWER, MC44S803_ADDR) |
	      MC44S803_REG_SM(0x200, MC44S803_POWER);

	err = mc44s803_writereg(priv, val);
	if (err)
		goto exit;

	msleep(10);

	val = MC44S803_REG_SM(MC44S803_REG_REFOSC, MC44S803_ADDR) |
	      MC44S803_REG_SM(0x40, MC44S803_REFOSC) |
	      MC44S803_REG_SM(1, MC44S803_OSCSEL);

	err = mc44s803_writereg(priv, val);
	if (err)
		goto exit;

	msleep(20);

/* Setup Mixer */

	val = MC44S803_REG_SM(MC44S803_REG_MIXER, MC44S803_ADDR) |
	      MC44S803_REG_SM(1, MC44S803_TRI_STATE) |
	      MC44S803_REG_SM(0x7F, MC44S803_MIXER_RES);

	err = mc44s803_writereg(priv, val);
	if (err)
		goto exit;

/* Setup Cirquit Adjust */

	val = MC44S803_REG_SM(MC44S803_REG_CIRCADJ, MC44S803_ADDR) |
	      MC44S803_REG_SM(1, MC44S803_G1) |
	      MC44S803_REG_SM(1, MC44S803_G3) |
	      MC44S803_REG_SM(0x3, MC44S803_CIRCADJ_RES) |
	      MC44S803_REG_SM(1, MC44S803_G6) |
	      MC44S803_REG_SM(priv->cfg->dig_out, MC44S803_S1) |
	      MC44S803_REG_SM(0x3, MC44S803_LP) |
	      MC44S803_REG_SM(1, MC44S803_CLRF) |
	      MC44S803_REG_SM(1, MC44S803_CLIF);

	err = mc44s803_writereg(priv, val);
	if (err)
		goto exit;

	val = MC44S803_REG_SM(MC44S803_REG_CIRCADJ, MC44S803_ADDR) |
	      MC44S803_REG_SM(1, MC44S803_G1) |
	      MC44S803_REG_SM(1, MC44S803_G3) |
	      MC44S803_REG_SM(0x3, MC44S803_CIRCADJ_RES) |
	      MC44S803_REG_SM(1, MC44S803_G6) |
	      MC44S803_REG_SM(priv->cfg->dig_out, MC44S803_S1) |
	      MC44S803_REG_SM(0x3, MC44S803_LP);

	err = mc44s803_writereg(priv, val);
	if (err)
		goto exit;

/* Setup Digtune */

	val = MC44S803_REG_SM(MC44S803_REG_DIGTUNE, MC44S803_ADDR) |
	      MC44S803_REG_SM(3, MC44S803_XOD);

	err = mc44s803_writereg(priv, val);
	if (err)
		goto exit;

/* Setup AGC */

	val = MC44S803_REG_SM(MC44S803_REG_LNAAGC, MC44S803_ADDR) |
	      MC44S803_REG_SM(1, MC44S803_AT1) |
	      MC44S803_REG_SM(1, MC44S803_AT2) |
	      MC44S803_REG_SM(1, MC44S803_AGC_AN_DIG) |
	      MC44S803_REG_SM(1, MC44S803_AGC_READ_EN) |
	      MC44S803_REG_SM(1, MC44S803_LNA0);

	err = mc44s803_writereg(priv, val);
	if (err)
		goto exit;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);
	return 0;

exit:
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	mc_printk(KERN_WARNING, "I/O Error\n");
	return err;
}