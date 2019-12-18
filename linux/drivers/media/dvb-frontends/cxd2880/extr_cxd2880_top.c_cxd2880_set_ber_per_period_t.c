#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct dvb_frontend {struct cxd2880_priv* demodulator_priv; } ;
struct cxd2880_tnrdmd {TYPE_2__* io; } ;
struct TYPE_4__ {int bandwidth; } ;
struct cxd2880_priv {unsigned int pre_ber_interval; unsigned int post_ber_interval; unsigned int ucblock_interval; struct cxd2880_tnrdmd tnrdmd; TYPE_1__ dvbt_tune_param; } ;
struct cxd2880_dvbt_tpsinfo {scalar_t__ hierarchy; int constellation; size_t guard; size_t rate_hp; size_t rate_lp; } ;
typedef  enum cxd2880_dtv_bandwidth { ____Placeholder_cxd2880_dtv_bandwidth } cxd2880_dtv_bandwidth ;
struct TYPE_5__ {int (* write_reg ) (TYPE_2__*,int /*<<< orphan*/ ,int,int) ;int (* read_regs ) (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 int CXD2880_DTV_BW_1_7_MHZ ; 
 void* CXD2880_DVBT_CODERATE_1_2 ; 
 int CXD2880_DVBT_CONSTELLATION_QPSK ; 
 size_t CXD2880_DVBT_GUARD_1_4 ; 
 scalar_t__ CXD2880_DVBT_HIERARCHY_NON ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 int /*<<< orphan*/  CXD2880_TNRDMD_CFG_DVBT_BERN_PERIOD ; 
 int /*<<< orphan*/  CXD2880_TNRDMD_CFG_DVBT_PER_MES ; 
 int /*<<< orphan*/  CXD2880_TNRDMD_CFG_DVBT_VBER_PERIOD ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_dvbt_mon_tps_info (struct cxd2880_tnrdmd*,struct cxd2880_dvbt_tpsinfo*) ; 
 int /*<<< orphan*/  cxd2880_tnrdmd_set_cfg (struct cxd2880_tnrdmd*,int /*<<< orphan*/ ,int) ; 
 int intlog2 (int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static int cxd2880_set_ber_per_period_t(struct dvb_frontend *fe)
{
	int ret;
	struct cxd2880_priv *priv;
	struct cxd2880_dvbt_tpsinfo info;
	enum cxd2880_dtv_bandwidth bw = CXD2880_DTV_BW_1_7_MHZ;
	u32 pre_ber_rate = 0;
	u32 post_ber_rate = 0;
	u32 ucblock_rate = 0;
	u32 mes_exp = 0;
	static const int cr_table[5] = {31500, 42000, 47250, 52500, 55125};
	static const int denominator_tbl[4] = {125664, 129472, 137088, 152320};

	if (!fe) {
		pr_err("invalid arg\n");
		return -EINVAL;
	}

	priv = fe->demodulator_priv;
	bw = priv->dvbt_tune_param.bandwidth;

	ret = cxd2880_tnrdmd_dvbt_mon_tps_info(&priv->tnrdmd,
					       &info);
	if (ret) {
		pr_err("tps monitor error ret = %d\n", ret);
		info.hierarchy = CXD2880_DVBT_HIERARCHY_NON;
		info.constellation = CXD2880_DVBT_CONSTELLATION_QPSK;
		info.guard = CXD2880_DVBT_GUARD_1_4;
		info.rate_hp = CXD2880_DVBT_CODERATE_1_2;
		info.rate_lp = CXD2880_DVBT_CODERATE_1_2;
	}

	if (info.hierarchy == CXD2880_DVBT_HIERARCHY_NON) {
		pre_ber_rate = 63000000 * bw * (info.constellation * 2 + 2) /
			       denominator_tbl[info.guard];

		post_ber_rate =	1000 * cr_table[info.rate_hp] * bw *
				(info.constellation * 2 + 2) /
				denominator_tbl[info.guard];

		ucblock_rate = 875 * cr_table[info.rate_hp] * bw *
			       (info.constellation * 2 + 2) /
			       denominator_tbl[info.guard];
	} else {
		u8 data = 0;
		struct cxd2880_tnrdmd *tnrdmd = &priv->tnrdmd;

		ret = tnrdmd->io->write_reg(tnrdmd->io,
					    CXD2880_IO_TGT_DMD,
					    0x00, 0x10);
		if (!ret) {
			ret = tnrdmd->io->read_regs(tnrdmd->io,
						    CXD2880_IO_TGT_DMD,
						    0x67, &data, 1);
			if (ret)
				data = 0x00;
		} else {
			data = 0x00;
		}

		if (data & 0x01) { /* Low priority */
			pre_ber_rate =
				63000000 * bw * (info.constellation * 2 + 2) /
				denominator_tbl[info.guard];

			post_ber_rate = 1000 * cr_table[info.rate_lp] * bw *
					(info.constellation * 2 + 2) /
					denominator_tbl[info.guard];

			ucblock_rate = (1000 * 7 / 8) *	cr_table[info.rate_lp] *
				       bw * (info.constellation * 2 + 2) /
				       denominator_tbl[info.guard];
		} else { /* High priority */
			pre_ber_rate =
				63000000 * bw * 2 / denominator_tbl[info.guard];

			post_ber_rate = 1000 * cr_table[info.rate_hp] * bw * 2 /
					denominator_tbl[info.guard];

			ucblock_rate = (1000 * 7 / 8) * cr_table[info.rate_hp] *
					bw * 2 / denominator_tbl[info.guard];
		}
	}

	mes_exp = pre_ber_rate < 8192 ? 8 : intlog2(pre_ber_rate) >> 24;
	priv->pre_ber_interval =
		((1U << mes_exp) * 1000 + (pre_ber_rate / 2)) /
		pre_ber_rate;
	cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
			       CXD2880_TNRDMD_CFG_DVBT_VBER_PERIOD,
			       mes_exp == 8 ? 0 : mes_exp - 12);

	mes_exp = intlog2(post_ber_rate) >> 24;
	priv->post_ber_interval =
		((1U << mes_exp) * 1000 + (post_ber_rate / 2)) /
		post_ber_rate;
	cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
			       CXD2880_TNRDMD_CFG_DVBT_BERN_PERIOD,
			       mes_exp);

	mes_exp = intlog2(ucblock_rate) >> 24;
	priv->ucblock_interval =
		((1U << mes_exp) * 1000 + (ucblock_rate / 2)) /
		ucblock_rate;
	cxd2880_tnrdmd_set_cfg(&priv->tnrdmd,
			       CXD2880_TNRDMD_CFG_DVBT_PER_MES,
			       mes_exp);

	return 0;
}