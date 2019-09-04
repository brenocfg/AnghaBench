#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dvb_frontend {struct cxd2880_priv* demodulator_priv; } ;
struct cxd2880_tnrdmd_create_param {int en_internal_ldo; int xosc_cap; int xosc_i; int stationary_use; int /*<<< orphan*/  xtal_share_type; int /*<<< orphan*/  ts_output_if; } ;
struct TYPE_4__ {int /*<<< orphan*/ * io; } ;
struct cxd2880_priv {int /*<<< orphan*/  spi_mutex; TYPE_1__ tnrdmd; int /*<<< orphan*/  regio; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXD2880_TNRDMD_CFG_TSPIN_CURRENT ; 
 int /*<<< orphan*/  CXD2880_TNRDMD_TSOUT_IF_SPI ; 
 int /*<<< orphan*/  CXD2880_TNRDMD_XTAL_SHARE_NONE ; 
 int EINVAL ; 
 int cxd2880_integ_init (TYPE_1__*) ; 
 int cxd2880_tnrdmd_create (TYPE_1__*,int /*<<< orphan*/ *,struct cxd2880_tnrdmd_create_param*) ; 
 int cxd2880_tnrdmd_set_cfg (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 

__attribute__((used)) static int cxd2880_init(struct dvb_frontend *fe)
{
	int ret;
	struct cxd2880_priv *priv = NULL;
	struct cxd2880_tnrdmd_create_param create_param;

	if (!fe) {
		pr_err("invalid arg.\n");
		return -EINVAL;
	}

	priv = fe->demodulator_priv;

	create_param.ts_output_if = CXD2880_TNRDMD_TSOUT_IF_SPI;
	create_param.xtal_share_type = CXD2880_TNRDMD_XTAL_SHARE_NONE;
	create_param.en_internal_ldo = 1;
	create_param.xosc_cap = 18;
	create_param.xosc_i = 8;
	create_param.stationary_use = 1;

	mutex_lock(priv->spi_mutex);
	if (priv->tnrdmd.io != &priv->regio) {
		ret = cxd2880_tnrdmd_create(&priv->tnrdmd,
					    &priv->regio, &create_param);
		if (ret) {
			mutex_unlock(priv->spi_mutex);
			pr_info("cxd2880 tnrdmd create failed %d\n", ret);
			return ret;
		}
	}
	ret = cxd2880_integ_init(&priv->tnrdmd);
	if (ret) {
		mutex_unlock(priv->spi_mutex);
		pr_err("cxd2880 integ init failed %d\n", ret);
		return ret;
	}

	ret = cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
				     CXD2880_TNRDMD_CFG_TSPIN_CURRENT,
				     0x00);
	if (ret) {
		mutex_unlock(priv->spi_mutex);
		pr_err("cxd2880 set config failed %d\n", ret);
		return ret;
	}
	mutex_unlock(priv->spi_mutex);

	pr_debug("OK.\n");

	return ret;
}