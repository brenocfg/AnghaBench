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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dtv_frontend_properties {int delivery_system; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct cxd2820r_priv* demodulator_priv; } ;
struct cxd2820r_priv {struct i2c_client** client; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int EINVAL ; 
#define  SYS_DVBC_ANNEX_A 130 
#define  SYS_DVBT 129 
#define  SYS_DVBT2 128 
 int cxd2820r_read_status_c (struct dvb_frontend*,int*) ; 
 int cxd2820r_read_status_t (struct dvb_frontend*,int*) ; 
 int cxd2820r_read_status_t2 (struct dvb_frontend*,int*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int cxd2820r_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct cxd2820r_priv *priv = fe->demodulator_priv;
	struct i2c_client *client = priv->client[0];
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	int ret;

	dev_dbg(&client->dev, "delivery_system=%d\n", c->delivery_system);

	switch (c->delivery_system) {
	case SYS_DVBT:
		ret = cxd2820r_read_status_t(fe, status);
		break;
	case SYS_DVBT2:
		ret = cxd2820r_read_status_t2(fe, status);
		break;
	case SYS_DVBC_ANNEX_A:
		ret = cxd2820r_read_status_c(fe, status);
		break;
	default:
		ret = -EINVAL;
		break;
	}
	return ret;
}