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
typedef  int /*<<< orphan*/  u32 ;
struct dtv_frontend_properties {scalar_t__ delivery_system; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct cxd2880_priv* demodulator_priv; } ;
struct cxd2880_priv {int /*<<< orphan*/  spi_mutex; int /*<<< orphan*/  tnrdmd; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SYS_DVBT ; 
 scalar_t__ SYS_DVBT2 ; 
 int cxd2880_tnrdmd_dvbt2_mon_packet_error_number (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cxd2880_tnrdmd_dvbt_mon_packet_error_number (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int cxd2880_read_ucblocks(struct dvb_frontend *fe, u32 *ucblocks)
{
	int ret;
	struct cxd2880_priv *priv = NULL;
	struct dtv_frontend_properties *c = NULL;

	if (!fe || !ucblocks) {
		pr_err("invalid arg\n");
		return -EINVAL;
	}

	priv = fe->demodulator_priv;
	c = &fe->dtv_property_cache;

	mutex_lock(priv->spi_mutex);
	if (c->delivery_system == SYS_DVBT) {
		ret = cxd2880_tnrdmd_dvbt_mon_packet_error_number(&priv->tnrdmd,
								  ucblocks);
	} else if (c->delivery_system == SYS_DVBT2) {
		ret = cxd2880_tnrdmd_dvbt2_mon_packet_error_number(&priv->tnrdmd,
								   ucblocks);
	} else {
		pr_err("invalid system\n");
		mutex_unlock(priv->spi_mutex);
		return -EINVAL;
	}
	mutex_unlock(priv->spi_mutex);

	if (ret)
		pr_debug("ret = %d\n", ret);

	return ret;
}