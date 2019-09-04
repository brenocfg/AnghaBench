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
struct cxd2820r_priv {int last_tune_failed; int delivery_system; struct i2c_client** client; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
typedef  enum dvbfe_search { ____Placeholder_dvbfe_search } dvbfe_search ;

/* Variables and functions */
 int DVBFE_ALGO_SEARCH_AGAIN ; 
 int DVBFE_ALGO_SEARCH_ERROR ; 
 int DVBFE_ALGO_SEARCH_SUCCESS ; 
 int FE_HAS_LOCK ; 
#define  SYS_DVBC_ANNEX_A 131 
#define  SYS_DVBT 130 
#define  SYS_DVBT2 129 
#define  SYS_UNDEFINED 128 
 int cxd2820r_read_status (struct dvb_frontend*,int*) ; 
 int cxd2820r_set_frontend (struct dvb_frontend*) ; 
 int cxd2820r_sleep_t (struct dvb_frontend*) ; 
 int cxd2820r_sleep_t2 (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static enum dvbfe_search cxd2820r_search(struct dvb_frontend *fe)
{
	struct cxd2820r_priv *priv = fe->demodulator_priv;
	struct i2c_client *client = priv->client[0];
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	int ret, i;
	enum fe_status status = 0;

	dev_dbg(&client->dev, "delivery_system=%d\n", c->delivery_system);

	/* switch between DVB-T and DVB-T2 when tune fails */
	if (priv->last_tune_failed) {
		if (priv->delivery_system == SYS_DVBT) {
			ret = cxd2820r_sleep_t(fe);
			if (ret)
				goto error;

			c->delivery_system = SYS_DVBT2;
		} else if (priv->delivery_system == SYS_DVBT2) {
			ret = cxd2820r_sleep_t2(fe);
			if (ret)
				goto error;

			c->delivery_system = SYS_DVBT;
		}
	}

	/* set frontend */
	ret = cxd2820r_set_frontend(fe);
	if (ret)
		goto error;

	/* frontend lock wait loop count */
	switch (priv->delivery_system) {
	case SYS_DVBT:
	case SYS_DVBC_ANNEX_A:
		i = 20;
		break;
	case SYS_DVBT2:
		i = 40;
		break;
	case SYS_UNDEFINED:
	default:
		i = 0;
		break;
	}

	/* wait frontend lock */
	for (; i > 0; i--) {
		dev_dbg(&client->dev, "loop=%d\n", i);
		msleep(50);
		ret = cxd2820r_read_status(fe, &status);
		if (ret)
			goto error;

		if (status & FE_HAS_LOCK)
			break;
	}

	/* check if we have a valid signal */
	if (status & FE_HAS_LOCK) {
		priv->last_tune_failed = false;
		return DVBFE_ALGO_SEARCH_SUCCESS;
	} else {
		priv->last_tune_failed = true;
		return DVBFE_ALGO_SEARCH_AGAIN;
	}

error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return DVBFE_ALGO_SEARCH_ERROR;
}