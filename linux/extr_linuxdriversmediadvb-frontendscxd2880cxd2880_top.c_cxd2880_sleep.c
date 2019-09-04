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
struct dvb_frontend {struct cxd2880_priv* demodulator_priv; } ;
struct cxd2880_priv {int /*<<< orphan*/  spi_mutex; int /*<<< orphan*/  tnrdmd; } ;

/* Variables and functions */
 int EINVAL ; 
 int cxd2880_tnrdmd_sleep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int cxd2880_sleep(struct dvb_frontend *fe)
{
	int ret;
	struct cxd2880_priv *priv = NULL;

	if (!fe) {
		pr_err("invalid arg\n");
		return -EINVAL;
	}

	priv = fe->demodulator_priv;

	mutex_lock(priv->spi_mutex);
	ret = cxd2880_tnrdmd_sleep(&priv->tnrdmd);
	mutex_unlock(priv->spi_mutex);

	pr_debug("tnrdmd_sleep ret %d\n", ret);

	return ret;
}