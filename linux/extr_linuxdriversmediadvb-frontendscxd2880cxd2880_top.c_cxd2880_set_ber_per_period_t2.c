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
typedef  int u8 ;
typedef  int u32 ;
struct dvb_frontend {struct cxd2880_priv* demodulator_priv; } ;
struct TYPE_2__ {int bandwidth; } ;
struct cxd2880_priv {unsigned int pre_ber_interval; unsigned int post_ber_interval; unsigned int ucblock_interval; int /*<<< orphan*/  tnrdmd; TYPE_1__ dvbt2_tune_param; } ;
struct cxd2880_dvbt2_plp {int til_len; int num_blocks_max; size_t fec; size_t plp_cr; scalar_t__ til_type; } ;
struct cxd2880_dvbt2_l1pre {size_t fft_mode; size_t gi; int const num_symbols; scalar_t__ mixed; } ;
struct cxd2880_dvbt2_l1post {int fef_intvl; int fef_length; } ;
struct cxd2880_dvbt2_bbheader {scalar_t__ plp_mode; int /*<<< orphan*/  issy_indicator; } ;
typedef  enum cxd2880_dtv_bandwidth { ____Placeholder_cxd2880_dtv_bandwidth } cxd2880_dtv_bandwidth ;

/* Variables and functions */
#define  CXD2880_DTV_BW_1_7_MHZ 132 
#define  CXD2880_DTV_BW_5_MHZ 131 
#define  CXD2880_DTV_BW_6_MHZ 130 
#define  CXD2880_DTV_BW_7_MHZ 129 
#define  CXD2880_DTV_BW_8_MHZ 128 
 int /*<<< orphan*/  CXD2880_DVBT2_PLP_DATA ; 
 scalar_t__ CXD2880_DVBT2_PLP_MODE_HEM ; 
 scalar_t__ CXD2880_DVBT2_PLP_MODE_NM ; 
 int /*<<< orphan*/  CXD2880_TNRDMD_CFG_DVBT2_BBER_MES ; 
 int /*<<< orphan*/  CXD2880_TNRDMD_CFG_DVBT2_LBER_MES ; 
 int /*<<< orphan*/  CXD2880_TNRDMD_CFG_DVBT2_PER_MES ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_dvbt2_mon_active_plp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cxd2880_dvbt2_plp*) ; 
 int cxd2880_tnrdmd_dvbt2_mon_bbheader (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cxd2880_dvbt2_bbheader*) ; 
 int cxd2880_tnrdmd_dvbt2_mon_l1_post (int /*<<< orphan*/ *,struct cxd2880_dvbt2_l1post*) ; 
 int cxd2880_tnrdmd_dvbt2_mon_l1_pre (int /*<<< orphan*/ *,struct cxd2880_dvbt2_l1pre*) ; 
 int /*<<< orphan*/  cxd2880_tnrdmd_set_cfg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int intlog2 (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int cxd2880_set_ber_per_period_t2(struct dvb_frontend *fe)
{
	int ret;
	struct cxd2880_priv *priv;
	struct cxd2880_dvbt2_l1pre l1pre;
	struct cxd2880_dvbt2_l1post l1post;
	struct cxd2880_dvbt2_plp plp;
	struct cxd2880_dvbt2_bbheader bbheader;
	enum cxd2880_dtv_bandwidth bw = CXD2880_DTV_BW_1_7_MHZ;
	u32 pre_ber_rate = 0;
	u32 post_ber_rate = 0;
	u32 ucblock_rate = 0;
	u32 mes_exp = 0;
	u32 term_a = 0;
	u32 term_b = 0;
	u32 denominator = 0;
	static const u32 gi_tbl[7] = {32, 64, 128, 256, 8, 152, 76};
	static const u8 n_tbl[6] = {8, 2, 4, 16, 1, 1};
	static const u8 mode_tbl[6] = {2, 8, 4, 1, 16, 32};
	static const u32 kbch_tbl[2][8] = {
		{6952, 9472, 10552, 11632, 12352, 13072, 5152, 6232},
		{32128, 38608, 42960, 48328, 51568, 53760, 0, 0}
	};

	if (!fe) {
		pr_err("invalid arg\n");
		return -EINVAL;
	}

	priv = fe->demodulator_priv;
	bw = priv->dvbt2_tune_param.bandwidth;

	ret = cxd2880_tnrdmd_dvbt2_mon_l1_pre(&priv->tnrdmd, &l1pre);
	if (ret) {
		pr_info("l1 pre error\n");
		goto error_ber_setting;
	}

	ret = cxd2880_tnrdmd_dvbt2_mon_active_plp(&priv->tnrdmd,
						  CXD2880_DVBT2_PLP_DATA, &plp);
	if (ret) {
		pr_info("plp info error\n");
		goto error_ber_setting;
	}

	ret = cxd2880_tnrdmd_dvbt2_mon_l1_post(&priv->tnrdmd, &l1post);
	if (ret) {
		pr_info("l1 post error\n");
		goto error_ber_setting;
	}

	term_a =
		(mode_tbl[l1pre.fft_mode] * (1024 + gi_tbl[l1pre.gi])) *
		(l1pre.num_symbols + n_tbl[l1pre.fft_mode]) + 2048;

	if (l1pre.mixed && l1post.fef_intvl) {
		term_b = (l1post.fef_length + (l1post.fef_intvl / 2)) /
			 l1post.fef_intvl;
	} else {
		term_b = 0;
	}

	switch (bw) {
	case CXD2880_DTV_BW_1_7_MHZ:
		denominator = ((term_a + term_b) * 71 + (131 / 2)) / 131;
		break;
	case CXD2880_DTV_BW_5_MHZ:
		denominator = ((term_a + term_b) * 7 + 20) / 40;
		break;
	case CXD2880_DTV_BW_6_MHZ:
		denominator = ((term_a + term_b) * 7 + 24) / 48;
		break;
	case CXD2880_DTV_BW_7_MHZ:
		denominator = ((term_a + term_b) + 4) / 8;
		break;
	case CXD2880_DTV_BW_8_MHZ:
	default:
		denominator = ((term_a + term_b) * 7 + 32) / 64;
		break;
	}

	if (plp.til_type && plp.til_len) {
		pre_ber_rate =
			(plp.num_blocks_max * 1000000 + (denominator / 2)) /
			denominator;
		pre_ber_rate = (pre_ber_rate + (plp.til_len / 2)) /
			       plp.til_len;
	} else {
		pre_ber_rate =
			(plp.num_blocks_max * 1000000 + (denominator / 2)) /
			denominator;
	}

	post_ber_rate = pre_ber_rate;

	mes_exp = intlog2(pre_ber_rate) >> 24;
	priv->pre_ber_interval =
		((1U << mes_exp) * 1000 + (pre_ber_rate / 2)) /
		pre_ber_rate;
	cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
			       CXD2880_TNRDMD_CFG_DVBT2_LBER_MES,
			       mes_exp);

	mes_exp = intlog2(post_ber_rate) >> 24;
	priv->post_ber_interval =
		((1U << mes_exp) * 1000 + (post_ber_rate / 2)) /
		post_ber_rate;
	cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
			       CXD2880_TNRDMD_CFG_DVBT2_BBER_MES,
			       mes_exp);

	ret = cxd2880_tnrdmd_dvbt2_mon_bbheader(&priv->tnrdmd,
						CXD2880_DVBT2_PLP_DATA,
						&bbheader);
	if (ret) {
		pr_info("bb header error\n");
		goto error_ucblock_setting;
	}

	if (bbheader.plp_mode == CXD2880_DVBT2_PLP_MODE_NM) {
		if (!bbheader.issy_indicator) {
			ucblock_rate =
				(pre_ber_rate * kbch_tbl[plp.fec][plp.plp_cr] +
				752) / 1504;
		} else {
			ucblock_rate =
				(pre_ber_rate * kbch_tbl[plp.fec][plp.plp_cr] +
				764) / 1528;
		}
	} else if (bbheader.plp_mode == CXD2880_DVBT2_PLP_MODE_HEM) {
		ucblock_rate =
			(pre_ber_rate * kbch_tbl[plp.fec][plp.plp_cr] + 748) /
			1496;
	} else {
		pr_info("plp mode is not Normal or HEM\n");
		goto error_ucblock_setting;
	}

	mes_exp = intlog2(ucblock_rate) >> 24;
	priv->ucblock_interval =
		((1U << mes_exp) * 1000 + (ucblock_rate / 2)) /
		ucblock_rate;
	cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
			       CXD2880_TNRDMD_CFG_DVBT2_PER_MES,
			       mes_exp);

	return 0;

error_ber_setting:
	priv->pre_ber_interval = 1000;
	cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
				     CXD2880_TNRDMD_CFG_DVBT2_LBER_MES, 0);

	priv->post_ber_interval = 1000;
	cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
			       CXD2880_TNRDMD_CFG_DVBT2_BBER_MES, 0);

error_ucblock_setting:
	priv->ucblock_interval = 1000;
	cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
			       CXD2880_TNRDMD_CFG_DVBT2_PER_MES, 8);

	return 0;
}