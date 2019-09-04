#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct dvb_frontend {struct cxd2880_priv* demodulator_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  tune_info; } ;
struct cxd2880_priv {TYPE_1__ dvbt2_tune_param; int /*<<< orphan*/  tnrdmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXD2880_TNRDMD_DVBT2_TUNE_INFO_INVALID_PLP_ID ; 
 int /*<<< orphan*/  CXD2880_TNRDMD_DVBT2_TUNE_INFO_OK ; 
 int EAGAIN ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_dvbt2_check_l1post_valid (int /*<<< orphan*/ *,scalar_t__*) ; 
 int cxd2880_tnrdmd_dvbt2_mon_data_plp_error (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int cxd2880_check_l1post_plp(struct dvb_frontend *fe)
{
	u8 valid = 0;
	u8 plp_not_found;
	int ret;
	struct cxd2880_priv *priv = NULL;

	if (!fe) {
		pr_err("invalid arg\n");
		return -EINVAL;
	}

	priv = fe->demodulator_priv;

	ret = cxd2880_tnrdmd_dvbt2_check_l1post_valid(&priv->tnrdmd,
						      &valid);
	if (ret)
		return ret;

	if (!valid)
		return -EAGAIN;

	ret = cxd2880_tnrdmd_dvbt2_mon_data_plp_error(&priv->tnrdmd,
						      &plp_not_found);
	if (ret)
		return ret;

	if (plp_not_found) {
		priv->dvbt2_tune_param.tune_info =
			CXD2880_TNRDMD_DVBT2_TUNE_INFO_INVALID_PLP_ID;
	} else {
		priv->dvbt2_tune_param.tune_info =
			CXD2880_TNRDMD_DVBT2_TUNE_INFO_OK;
	}

	return 0;
}