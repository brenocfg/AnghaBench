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
typedef  int u16 ;
struct tda8290_priv {int /*<<< orphan*/  i2c_props; } ;
struct dvb_frontend {struct tda8290_priv* analog_demod_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (unsigned char*) ; 
 int /*<<< orphan*/  tuner_i2c_xfer_send_recv (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int tda8290_has_signal(struct dvb_frontend *fe, u16 *signal)
{
	struct tda8290_priv *priv = fe->analog_demod_priv;

	unsigned char i2c_get_afc[1] = { 0x1B };
	unsigned char afc = 0;

	tuner_i2c_xfer_send_recv(&priv->i2c_props,
				 i2c_get_afc, ARRAY_SIZE(i2c_get_afc), &afc, 1);
	*signal = (afc & 0x80) ? 65535 : 0;
	return 0;
}