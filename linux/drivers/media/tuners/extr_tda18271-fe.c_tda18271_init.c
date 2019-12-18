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
struct tda18271_priv {scalar_t__ id; int /*<<< orphan*/  lock; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;

/* Variables and functions */
 scalar_t__ TDA18271HDC2 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tda18271_ir_cal_init (struct dvb_frontend*) ; 
 int tda18271_set_standby_mode (struct dvb_frontend*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda18271c2_rf_cal_init (struct dvb_frontend*) ; 
 scalar_t__ tda_fail (int) ; 

__attribute__((used)) static int tda18271_init(struct dvb_frontend *fe)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	int ret;

	mutex_lock(&priv->lock);

	/* full power up */
	ret = tda18271_set_standby_mode(fe, 0, 0, 0);
	if (tda_fail(ret))
		goto fail;

	/* initialization */
	ret = tda18271_ir_cal_init(fe);
	if (tda_fail(ret))
		goto fail;

	if (priv->id == TDA18271HDC2)
		tda18271c2_rf_cal_init(fe);
fail:
	mutex_unlock(&priv->lock);

	return ret;
}