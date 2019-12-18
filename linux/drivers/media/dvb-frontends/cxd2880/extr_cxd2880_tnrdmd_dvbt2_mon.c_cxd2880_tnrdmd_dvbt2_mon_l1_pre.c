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
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; scalar_t__ sys; TYPE_1__* io; } ;
struct cxd2880_dvbt2_l1pre {int type; int bw_ext; int s1; int s2; int l1_rep; int gi; int papr; int mod; int cr; int fec; int l1_post_size; int l1_post_info_size; int pp; int tx_id_availability; int cell_id; int network_id; int sys_id; int num_frames; int num_symbols; int regen; int post_ext; int num_rf_freqs; int rf_idx; int t2_version; int l1_post_scrambled; int t2_base_lite; int crc32; int mixed; void* fft_mode; } ;
typedef  enum cxd2880_dvbt2_version { ____Placeholder_cxd2880_dvbt2_version } cxd2880_dvbt2_version ;
typedef  enum cxd2880_dvbt2_s1 { ____Placeholder_cxd2880_dvbt2_s1 } cxd2880_dvbt2_s1 ;
typedef  enum cxd2880_dvbt2_profile { ____Placeholder_cxd2880_dvbt2_profile } cxd2880_dvbt2_profile ;
typedef  enum cxd2880_dvbt2_pp { ____Placeholder_cxd2880_dvbt2_pp } cxd2880_dvbt2_pp ;
typedef  enum cxd2880_dvbt2_papr { ____Placeholder_cxd2880_dvbt2_papr } cxd2880_dvbt2_papr ;
typedef  enum cxd2880_dvbt2_l1pre_type { ____Placeholder_cxd2880_dvbt2_l1pre_type } cxd2880_dvbt2_l1pre_type ;
typedef  enum cxd2880_dvbt2_l1post_fec_type { ____Placeholder_cxd2880_dvbt2_l1post_fec_type } cxd2880_dvbt2_l1post_fec_type ;
typedef  enum cxd2880_dvbt2_l1post_cr { ____Placeholder_cxd2880_dvbt2_l1post_cr } cxd2880_dvbt2_l1post_cr ;
typedef  enum cxd2880_dvbt2_l1post_constell { ____Placeholder_cxd2880_dvbt2_l1post_constell } cxd2880_dvbt2_l1post_constell ;
typedef  enum cxd2880_dvbt2_guard { ____Placeholder_cxd2880_dvbt2_guard } cxd2880_dvbt2_guard ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_3__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* read_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 scalar_t__ CXD2880_DTV_SYS_DVBT2 ; 
#define  CXD2880_DVBT2_BASE_S2_M16K_G_ANY 141 
#define  CXD2880_DVBT2_BASE_S2_M1K_G_ANY 140 
#define  CXD2880_DVBT2_BASE_S2_M2K_G_ANY 139 
#define  CXD2880_DVBT2_BASE_S2_M32K_G_DVBT 138 
#define  CXD2880_DVBT2_BASE_S2_M32K_G_DVBT2 137 
#define  CXD2880_DVBT2_BASE_S2_M4K_G_ANY 136 
#define  CXD2880_DVBT2_BASE_S2_M8K_G_DVBT 135 
#define  CXD2880_DVBT2_BASE_S2_M8K_G_DVBT2 134 
#define  CXD2880_DVBT2_LITE_S2_M16K_G_DVBT 133 
#define  CXD2880_DVBT2_LITE_S2_M16K_G_DVBT2 132 
#define  CXD2880_DVBT2_LITE_S2_M2K_G_ANY 131 
#define  CXD2880_DVBT2_LITE_S2_M4K_G_ANY 130 
#define  CXD2880_DVBT2_LITE_S2_M8K_G_DVBT 129 
#define  CXD2880_DVBT2_LITE_S2_M8K_G_DVBT2 128 
 void* CXD2880_DVBT2_M16K ; 
 void* CXD2880_DVBT2_M1K ; 
 void* CXD2880_DVBT2_M2K ; 
 void* CXD2880_DVBT2_M32K ; 
 void* CXD2880_DVBT2_M4K ; 
 void* CXD2880_DVBT2_M8K ; 
 int CXD2880_DVBT2_PROFILE_BASE ; 
 int CXD2880_DVBT2_PROFILE_LITE ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_MAIN ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SUB ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_dvbt2_mon_profile (struct cxd2880_tnrdmd*,int*) ; 
 int cxd2880_tnrdmd_dvbt2_mon_sync_stat (struct cxd2880_tnrdmd*,int*,int*,int*) ; 
 int cxd2880_tnrdmd_dvbt2_mon_sync_stat_sub (struct cxd2880_tnrdmd*,int*,int*) ; 
 int slvt_freeze_reg (struct cxd2880_tnrdmd*) ; 
 int /*<<< orphan*/  slvt_unfreeze_reg (struct cxd2880_tnrdmd*) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 

int cxd2880_tnrdmd_dvbt2_mon_l1_pre(struct cxd2880_tnrdmd *tnr_dmd,
				    struct cxd2880_dvbt2_l1pre
				    *l1_pre)
{
	u8 data[37];
	u8 sync_state = 0;
	u8 ts_lock = 0;
	u8 unlock_detected = 0;
	u8 version = 0;
	enum cxd2880_dvbt2_profile profile;
	int ret;

	if (!tnr_dmd || !l1_pre)
		return -EINVAL;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	if (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		return -EINVAL;

	ret = slvt_freeze_reg(tnr_dmd);
	if (ret)
		return ret;

	ret =
	    cxd2880_tnrdmd_dvbt2_mon_sync_stat(tnr_dmd, &sync_state,
					       &ts_lock,
					       &unlock_detected);
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	if (sync_state < 5) {
		if (tnr_dmd->diver_mode ==
		    CXD2880_TNRDMD_DIVERMODE_MAIN) {
			ret =
			    cxd2880_tnrdmd_dvbt2_mon_sync_stat_sub
			    (tnr_dmd, &sync_state, &unlock_detected);
			if (ret) {
				slvt_unfreeze_reg(tnr_dmd);
				return ret;
			}

			if (sync_state < 5) {
				slvt_unfreeze_reg(tnr_dmd);
				return -EAGAIN;
			}
		} else {
			slvt_unfreeze_reg(tnr_dmd);
			return -EAGAIN;
		}
	}

	ret = cxd2880_tnrdmd_dvbt2_mon_profile(tnr_dmd, &profile);
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x61, data, sizeof(data));
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}
	slvt_unfreeze_reg(tnr_dmd);

	l1_pre->type = (enum cxd2880_dvbt2_l1pre_type)data[0];
	l1_pre->bw_ext = data[1] & 0x01;
	l1_pre->s1 = (enum cxd2880_dvbt2_s1)(data[2] & 0x07);
	l1_pre->s2 = data[3] & 0x0f;
	l1_pre->l1_rep = data[4] & 0x01;
	l1_pre->gi = (enum cxd2880_dvbt2_guard)(data[5] & 0x07);
	l1_pre->papr = (enum cxd2880_dvbt2_papr)(data[6] & 0x0f);
	l1_pre->mod =
	    (enum cxd2880_dvbt2_l1post_constell)(data[7] & 0x0f);
	l1_pre->cr = (enum cxd2880_dvbt2_l1post_cr)(data[8] & 0x03);
	l1_pre->fec =
	    (enum cxd2880_dvbt2_l1post_fec_type)(data[9] & 0x03);
	l1_pre->l1_post_size = (data[10] & 0x03) << 16;
	l1_pre->l1_post_size |= (data[11]) << 8;
	l1_pre->l1_post_size |= (data[12]);
	l1_pre->l1_post_info_size = (data[13] & 0x03) << 16;
	l1_pre->l1_post_info_size |= (data[14]) << 8;
	l1_pre->l1_post_info_size |= (data[15]);
	l1_pre->pp = (enum cxd2880_dvbt2_pp)(data[16] & 0x0f);
	l1_pre->tx_id_availability = data[17];
	l1_pre->cell_id = (data[18] << 8);
	l1_pre->cell_id |= (data[19]);
	l1_pre->network_id = (data[20] << 8);
	l1_pre->network_id |= (data[21]);
	l1_pre->sys_id = (data[22] << 8);
	l1_pre->sys_id |= (data[23]);
	l1_pre->num_frames = data[24];
	l1_pre->num_symbols = (data[25] & 0x0f) << 8;
	l1_pre->num_symbols |= data[26];
	l1_pre->regen = data[27] & 0x07;
	l1_pre->post_ext = data[28] & 0x01;
	l1_pre->num_rf_freqs = data[29] & 0x07;
	l1_pre->rf_idx = data[30] & 0x07;
	version = (data[31] & 0x03) << 2;
	version |= (data[32] & 0xc0) >> 6;
	l1_pre->t2_version = (enum cxd2880_dvbt2_version)version;
	l1_pre->l1_post_scrambled = (data[32] & 0x20) >> 5;
	l1_pre->t2_base_lite = (data[32] & 0x10) >> 4;
	l1_pre->crc32 = (data[33] << 24);
	l1_pre->crc32 |= (data[34] << 16);
	l1_pre->crc32 |= (data[35] << 8);
	l1_pre->crc32 |= data[36];

	if (profile == CXD2880_DVBT2_PROFILE_BASE) {
		switch ((l1_pre->s2 >> 1)) {
		case CXD2880_DVBT2_BASE_S2_M1K_G_ANY:
			l1_pre->fft_mode = CXD2880_DVBT2_M1K;
			break;
		case CXD2880_DVBT2_BASE_S2_M2K_G_ANY:
			l1_pre->fft_mode = CXD2880_DVBT2_M2K;
			break;
		case CXD2880_DVBT2_BASE_S2_M4K_G_ANY:
			l1_pre->fft_mode = CXD2880_DVBT2_M4K;
			break;
		case CXD2880_DVBT2_BASE_S2_M8K_G_DVBT:
		case CXD2880_DVBT2_BASE_S2_M8K_G_DVBT2:
			l1_pre->fft_mode = CXD2880_DVBT2_M8K;
			break;
		case CXD2880_DVBT2_BASE_S2_M16K_G_ANY:
			l1_pre->fft_mode = CXD2880_DVBT2_M16K;
			break;
		case CXD2880_DVBT2_BASE_S2_M32K_G_DVBT:
		case CXD2880_DVBT2_BASE_S2_M32K_G_DVBT2:
			l1_pre->fft_mode = CXD2880_DVBT2_M32K;
			break;
		default:
			return -EAGAIN;
		}
	} else if (profile == CXD2880_DVBT2_PROFILE_LITE) {
		switch ((l1_pre->s2 >> 1)) {
		case CXD2880_DVBT2_LITE_S2_M2K_G_ANY:
			l1_pre->fft_mode = CXD2880_DVBT2_M2K;
			break;
		case CXD2880_DVBT2_LITE_S2_M4K_G_ANY:
			l1_pre->fft_mode = CXD2880_DVBT2_M4K;
			break;
		case CXD2880_DVBT2_LITE_S2_M8K_G_DVBT:
		case CXD2880_DVBT2_LITE_S2_M8K_G_DVBT2:
			l1_pre->fft_mode = CXD2880_DVBT2_M8K;
			break;
		case CXD2880_DVBT2_LITE_S2_M16K_G_DVBT:
		case CXD2880_DVBT2_LITE_S2_M16K_G_DVBT2:
			l1_pre->fft_mode = CXD2880_DVBT2_M16K;
			break;
		default:
			return -EAGAIN;
		}
	} else {
		return -EAGAIN;
	}

	l1_pre->mixed = l1_pre->s2 & 0x01;

	return ret;
}