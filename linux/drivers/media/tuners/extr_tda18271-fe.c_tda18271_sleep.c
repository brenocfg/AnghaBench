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
struct tda18271_priv {int /*<<< orphan*/  lock; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tda18271_toggle_output (struct dvb_frontend*,int) ; 

__attribute__((used)) static int tda18271_sleep(struct dvb_frontend *fe)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	int ret;

	mutex_lock(&priv->lock);

	/* enter standby mode, with required output features enabled */
	ret = tda18271_toggle_output(fe, 1);

	mutex_unlock(&priv->lock);

	return ret;
}