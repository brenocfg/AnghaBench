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
typedef  scalar_t__ u32 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  delivery_system; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct cxd2820r_priv* demodulator_priv; } ;
struct cxd2820r_priv {scalar_t__ post_bit_error; scalar_t__ post_bit_error_prev_dvbv3; struct i2c_client** client; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxd2820r_read_ber(struct dvb_frontend *fe, u32 *ber)
{
	struct cxd2820r_priv *priv = fe->demodulator_priv;
	struct i2c_client *client = priv->client[0];
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;

	dev_dbg(&client->dev, "delivery_system=%d\n", c->delivery_system);

	*ber = (priv->post_bit_error - priv->post_bit_error_prev_dvbv3);
	priv->post_bit_error_prev_dvbv3 = priv->post_bit_error;

	return 0;
}