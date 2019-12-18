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
struct tda827x_priv {TYPE_2__* i2c_adap; TYPE_1__* cfg; } ;
struct i2c_msg {unsigned char* buf; int len; int /*<<< orphan*/  addr; int /*<<< orphan*/  flags; } ;
struct dvb_frontend {int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;struct tda827x_priv* tuner_priv; } ;
struct analog_parameters {int std; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int /*<<< orphan*/  algo_data; } ;
struct TYPE_3__ {int config; int /*<<< orphan*/  switch_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVB_FRONTEND_COMPONENT_TUNER ; 
#define  TDA8290_LNA_GP0_HIGH_OFF 131 
#define  TDA8290_LNA_GP0_HIGH_ON 130 
#define  TDA8290_LNA_OFF 129 
#define  TDA8290_LNA_ON_BRIDGE 128 
 int V4L2_STD_MN ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tuner_transfer (struct dvb_frontend*,struct i2c_msg*,int) ; 

__attribute__((used)) static void tda827xa_lna_gain(struct dvb_frontend *fe, int high,
			      struct analog_parameters *params)
{
	struct tda827x_priv *priv = fe->tuner_priv;
	unsigned char buf[] = {0x22, 0x01};
	int arg;
	int gp_func;
	struct i2c_msg msg = { .flags = 0, .buf = buf, .len = sizeof(buf) };

	if (NULL == priv->cfg) {
		dprintk("tda827x_config not defined, cannot set LNA gain!\n");
		return;
	}
	msg.addr = priv->cfg->switch_addr;
	if (priv->cfg->config) {
		if (high)
			dprintk("setting LNA to high gain\n");
		else
			dprintk("setting LNA to low gain\n");
	}
	switch (priv->cfg->config) {
	case TDA8290_LNA_OFF: /* no LNA */
		break;
	case TDA8290_LNA_GP0_HIGH_ON: /* switch is GPIO 0 of tda8290 */
	case TDA8290_LNA_GP0_HIGH_OFF:
		if (params == NULL) {
			gp_func = 0;
			arg  = 0;
		} else {
			/* turn Vsync on */
			gp_func = 1;
			if (params->std & V4L2_STD_MN)
				arg = 1;
			else
				arg = 0;
		}
		if (fe->callback)
			fe->callback(priv->i2c_adap->algo_data,
				     DVB_FRONTEND_COMPONENT_TUNER,
				     gp_func, arg);
		buf[1] = high ? 0 : 1;
		if (priv->cfg->config == TDA8290_LNA_GP0_HIGH_OFF)
			buf[1] = high ? 1 : 0;
		tuner_transfer(fe, &msg, 1);
		break;
	case TDA8290_LNA_ON_BRIDGE: /* switch with GPIO of saa713x */
		if (fe->callback)
			fe->callback(priv->i2c_adap->algo_data,
				     DVB_FRONTEND_COMPONENT_TUNER, 0, high);
		break;
	}
}