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
struct cxd2880_tnrdmd {scalar_t__ state; scalar_t__ sys; scalar_t__ diver_mode; TYPE_1__* io; struct cxd2880_tnrdmd* diver_sub; } ;
struct cxd2880_dvbt2_ofdm {int mixed; int is_miso; int mode; int gi; int pp; int bw_ext; int papr; int num_symbols; } ;
typedef  enum cxd2880_dvbt2_pp { ____Placeholder_cxd2880_dvbt2_pp } cxd2880_dvbt2_pp ;
typedef  enum cxd2880_dvbt2_papr { ____Placeholder_cxd2880_dvbt2_papr } cxd2880_dvbt2_papr ;
typedef  enum cxd2880_dvbt2_mode { ____Placeholder_cxd2880_dvbt2_mode } cxd2880_dvbt2_mode ;
typedef  enum cxd2880_dvbt2_guard { ____Placeholder_cxd2880_dvbt2_guard } cxd2880_dvbt2_guard ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_3__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* read_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 scalar_t__ CXD2880_DTV_SYS_DVBT2 ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_MAIN ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_dvbt2_mon_sync_stat (struct cxd2880_tnrdmd*,int*,int*,int*) ; 
 int slvt_freeze_reg (struct cxd2880_tnrdmd*) ; 
 int /*<<< orphan*/  slvt_unfreeze_reg (struct cxd2880_tnrdmd*) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 

int cxd2880_tnrdmd_dvbt2_mon_ofdm(struct cxd2880_tnrdmd *tnr_dmd,
				  struct cxd2880_dvbt2_ofdm *ofdm)
{
	u8 data[5];
	u8 sync_state = 0;
	u8 ts_lock = 0;
	u8 unlock_detected = 0;
	int ret;

	if (!tnr_dmd || !ofdm)
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

	if (sync_state != 6) {
		slvt_unfreeze_reg(tnr_dmd);

		ret = -EAGAIN;

		if (tnr_dmd->diver_mode ==
		    CXD2880_TNRDMD_DIVERMODE_MAIN)
			ret =
			    cxd2880_tnrdmd_dvbt2_mon_ofdm(tnr_dmd->diver_sub,
							  ofdm);

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
				     0x1d, data, sizeof(data));
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	slvt_unfreeze_reg(tnr_dmd);

	ofdm->mixed = ((data[0] & 0x20) ? 1 : 0);
	ofdm->is_miso = ((data[0] & 0x10) >> 4);
	ofdm->mode = (enum cxd2880_dvbt2_mode)(data[0] & 0x07);
	ofdm->gi = (enum cxd2880_dvbt2_guard)((data[1] & 0x70) >> 4);
	ofdm->pp = (enum cxd2880_dvbt2_pp)(data[1] & 0x07);
	ofdm->bw_ext = (data[2] & 0x10) >> 4;
	ofdm->papr = (enum cxd2880_dvbt2_papr)(data[2] & 0x0f);
	ofdm->num_symbols = (data[3] << 8) | data[4];

	return 0;
}