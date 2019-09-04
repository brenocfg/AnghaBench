#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct dtv_frontend_properties {scalar_t__ delivery_system; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct cxd2880_priv* demodulator_priv; } ;
struct TYPE_3__ {scalar_t__ state; int /*<<< orphan*/  sys; } ;
struct cxd2880_priv {int s; int /*<<< orphan*/  spi_mutex; TYPE_1__ tnrdmd; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EINVAL ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 scalar_t__ SYS_DVBT ; 
 scalar_t__ SYS_DVBT2 ; 
 int cxd2880_check_l1post_plp (struct dvb_frontend*) ; 
 int /*<<< orphan*/  cxd2880_get_stats (struct dvb_frontend*,int) ; 
 int cxd2880_set_ber_per_period_t (struct dvb_frontend*) ; 
 int cxd2880_set_ber_per_period_t2 (struct dvb_frontend*) ; 
 int cxd2880_tnrdmd_dvbt2_mon_sync_stat (TYPE_1__*,int*,int*,int*) ; 
 int cxd2880_tnrdmd_dvbt_mon_sync_stat (TYPE_1__*,int*,int*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int cxd2880_read_status(struct dvb_frontend *fe,
			       enum fe_status *status)
{
	int ret;
	u8 sync = 0;
	u8 lock = 0;
	u8 unlock = 0;
	struct cxd2880_priv *priv = NULL;
	struct dtv_frontend_properties *c = NULL;

	if (!fe || !status) {
		pr_err("invalid arg\n");
		return -EINVAL;
	}

	priv = fe->demodulator_priv;
	c = &fe->dtv_property_cache;
	*status = 0;

	if (priv->tnrdmd.state == CXD2880_TNRDMD_STATE_ACTIVE) {
		mutex_lock(priv->spi_mutex);
		if (c->delivery_system == SYS_DVBT) {
			ret = cxd2880_tnrdmd_dvbt_mon_sync_stat(&priv->tnrdmd,
								&sync,
								&lock,
								&unlock);
		} else if (c->delivery_system == SYS_DVBT2) {
			ret = cxd2880_tnrdmd_dvbt2_mon_sync_stat(&priv->tnrdmd,
								 &sync,
								 &lock,
								 &unlock);
		} else {
			pr_err("invalid system");
			mutex_unlock(priv->spi_mutex);
			return -EINVAL;
		}

		mutex_unlock(priv->spi_mutex);
		if (ret) {
			pr_err("failed. sys = %d\n", priv->tnrdmd.sys);
			return  ret;
		}

		if (sync == 6) {
			*status = FE_HAS_SIGNAL |
				  FE_HAS_CARRIER;
		}
		if (lock)
			*status |= FE_HAS_VITERBI |
				   FE_HAS_SYNC |
				   FE_HAS_LOCK;
	}

	pr_debug("status %d\n", *status);

	if (priv->s == 0 && (*status & FE_HAS_LOCK) &&
	    (*status & FE_HAS_CARRIER)) {
		mutex_lock(priv->spi_mutex);
		if (c->delivery_system == SYS_DVBT) {
			ret = cxd2880_set_ber_per_period_t(fe);
			priv->s = *status;
		} else if (c->delivery_system == SYS_DVBT2) {
			ret = cxd2880_check_l1post_plp(fe);
			if (!ret) {
				ret = cxd2880_set_ber_per_period_t2(fe);
				priv->s = *status;
			}
		} else {
			pr_err("invalid system\n");
			mutex_unlock(priv->spi_mutex);
			return -EINVAL;
		}
		mutex_unlock(priv->spi_mutex);
	}

	cxd2880_get_stats(fe, *status);
	return  0;
}