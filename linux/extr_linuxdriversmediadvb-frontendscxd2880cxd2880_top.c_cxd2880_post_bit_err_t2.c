#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  unsigned int u32 ;
typedef  unsigned int u16 ;
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; scalar_t__ sys; TYPE_1__* io; } ;
typedef  enum cxd2880_dvbt2_plp_fec { ____Placeholder_cxd2880_dvbt2_plp_fec } cxd2880_dvbt2_plp_fec ;
typedef  enum cxd2880_dvbt2_plp_code_rate { ____Placeholder_cxd2880_dvbt2_plp_code_rate } cxd2880_dvbt2_plp_code_rate ;
struct TYPE_7__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* read_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 scalar_t__ CXD2880_DTV_SYS_DVBT2 ; 
 int CXD2880_DVBT2_FEC_LDPC_16K ; 
 int CXD2880_DVBT2_FEC_LDPC_64K ; 
 int CXD2880_DVBT2_R1_2 ; 
 int CXD2880_DVBT2_R2_5 ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SUB ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int slvt_freeze_reg (struct cxd2880_tnrdmd*) ; 
 int /*<<< orphan*/  slvt_unfreeze_reg (struct cxd2880_tnrdmd*) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub3 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub4 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub5 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub6 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static int cxd2880_post_bit_err_t2(struct cxd2880_tnrdmd *tnrdmd,
				   u32 *post_bit_err,
				   u32 *post_bit_count)
{
	u32 period_exp = 0;
	u32 n_bch = 0;
	u8 data[3];
	enum cxd2880_dvbt2_plp_fec plp_fec_type =
		CXD2880_DVBT2_FEC_LDPC_16K;
	enum cxd2880_dvbt2_plp_code_rate plp_code_rate =
		CXD2880_DVBT2_R1_2;
	int ret;
	static const u16 n_bch_bits_lookup[2][8] = {
		{7200, 9720, 10800, 11880, 12600, 13320, 5400, 6480},
		{32400, 38880, 43200, 48600, 51840, 54000, 21600, 25920}
	};

	if (!tnrdmd || !post_bit_err || !post_bit_count)
		return -EINVAL;

	if (tnrdmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		return -EINVAL;

	if (tnrdmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	if (tnrdmd->sys != CXD2880_DTV_SYS_DVBT2)
		return -EINVAL;

	ret = slvt_freeze_reg(tnrdmd);
	if (ret)
		return ret;

	ret = tnrdmd->io->write_reg(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x0b);
	if (ret) {
		slvt_unfreeze_reg(tnrdmd);
		return ret;
	}

	ret = tnrdmd->io->read_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x15, data, 3);
	if (ret) {
		slvt_unfreeze_reg(tnrdmd);
		return ret;
	}

	if (!(data[0] & 0x40)) {
		slvt_unfreeze_reg(tnrdmd);
		return -EAGAIN;
	}

	*post_bit_err =
		((data[0] & 0x3f) << 16) | (data[1] << 8) | data[2];

	ret = tnrdmd->io->read_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x9d, data, 1);
	if (ret) {
		slvt_unfreeze_reg(tnrdmd);
		return ret;
	}

	plp_code_rate =
	(enum cxd2880_dvbt2_plp_code_rate)(data[0] & 0x07);

	ret = tnrdmd->io->read_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0xa0, data, 1);
	if (ret) {
		slvt_unfreeze_reg(tnrdmd);
		return ret;
	}

	plp_fec_type = (enum cxd2880_dvbt2_plp_fec)(data[0] & 0x03);

	slvt_unfreeze_reg(tnrdmd);

	ret = tnrdmd->io->write_reg(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x20);
	if (ret)
		return ret;

	ret = tnrdmd->io->read_regs(tnrdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x72, data, 1);
	if (ret)
		return ret;

	period_exp = data[0] & 0x0f;

	if (plp_fec_type > CXD2880_DVBT2_FEC_LDPC_64K ||
	    plp_code_rate > CXD2880_DVBT2_R2_5)
		return -EAGAIN;

	n_bch = n_bch_bits_lookup[plp_fec_type][plp_code_rate];

	if (*post_bit_err > ((1U << period_exp) * n_bch))
		return -EAGAIN;

	*post_bit_count = (1U << period_exp) * n_bch;

	return 0;
}