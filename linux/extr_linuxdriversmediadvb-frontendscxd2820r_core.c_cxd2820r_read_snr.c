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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_2__ cnr; int /*<<< orphan*/  delivery_system; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct cxd2820r_priv* demodulator_priv; } ;
struct cxd2820r_priv {struct i2c_client** client; } ;
struct TYPE_3__ {scalar_t__ scale; int /*<<< orphan*/  svalue; } ;

/* Variables and functions */
 scalar_t__ FE_SCALE_DECIBEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div_s64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cxd2820r_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	struct cxd2820r_priv *priv = fe->demodulator_priv;
	struct i2c_client *client = priv->client[0];
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;

	dev_dbg(&client->dev, "delivery_system=%d\n", c->delivery_system);

	if (c->cnr.stat[0].scale == FE_SCALE_DECIBEL)
		*snr = div_s64(c->cnr.stat[0].svalue, 100);
	else
		*snr = 0;

	return 0;
}