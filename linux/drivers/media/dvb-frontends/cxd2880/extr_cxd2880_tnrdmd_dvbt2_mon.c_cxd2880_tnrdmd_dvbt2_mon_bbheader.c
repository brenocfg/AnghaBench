#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; scalar_t__ sys; TYPE_1__* io; } ;
struct cxd2880_dvbt2_bbheader {int stream_input; int is_single_input_stream; int is_constant_coding_modulation; int issy_indicator; int null_packet_deletion; int ext; int input_stream_identifier; scalar_t__ plp_mode; int data_field_length; int user_packet_length; int sync_byte; int issy; } ;
typedef  enum cxd2880_dvbt2_stream { ____Placeholder_cxd2880_dvbt2_stream } cxd2880_dvbt2_stream ;
typedef  enum cxd2880_dvbt2_plp_btype { ____Placeholder_cxd2880_dvbt2_plp_btype } cxd2880_dvbt2_plp_btype ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_5__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* read_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 scalar_t__ CXD2880_DTV_SYS_DVBT2 ; 
 int CXD2880_DVBT2_PLP_COMMON ; 
 scalar_t__ CXD2880_DVBT2_PLP_MODE_HEM ; 
 scalar_t__ CXD2880_DVBT2_PLP_MODE_NM ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SUB ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_dvbt2_mon_sync_stat (struct cxd2880_tnrdmd*,int*,int*,int*) ; 
 int slvt_freeze_reg (struct cxd2880_tnrdmd*) ; 
 int /*<<< orphan*/  slvt_unfreeze_reg (struct cxd2880_tnrdmd*) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub3 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 
 int stub4 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 

int cxd2880_tnrdmd_dvbt2_mon_bbheader(struct cxd2880_tnrdmd
				      *tnr_dmd,
				      enum cxd2880_dvbt2_plp_btype
				      type,
				      struct cxd2880_dvbt2_bbheader
				      *bbheader)
{
	u8 sync_state = 0;
	u8 ts_lock = 0;
	u8 unlock_detected = 0;
	u8 data[14];
	u8 addr = 0;
	int ret;

	if (!tnr_dmd || !bbheader)
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

	if (!ts_lock) {
		slvt_unfreeze_reg(tnr_dmd);
		return -EAGAIN;
	}

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	if (type == CXD2880_DVBT2_PLP_COMMON) {
		u8 l1_post_ok;
		u8 data;

		ret = tnr_dmd->io->read_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x86, &l1_post_ok, 1);
		if (ret) {
			slvt_unfreeze_reg(tnr_dmd);
			return ret;
		}

		if (!(l1_post_ok & 0x01)) {
			slvt_unfreeze_reg(tnr_dmd);
			return -EAGAIN;
		}

		ret = tnr_dmd->io->read_regs(tnr_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0xb6, &data, 1);
		if (ret) {
			slvt_unfreeze_reg(tnr_dmd);
			return ret;
		}

		if (data == 0) {
			slvt_unfreeze_reg(tnr_dmd);
			return -EAGAIN;
		}
	}

	if (type == CXD2880_DVBT2_PLP_COMMON)
		addr = 0x51;
	else
		addr = 0x42;

	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     addr, data, sizeof(data));
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	slvt_unfreeze_reg(tnr_dmd);

	bbheader->stream_input =
	    (enum cxd2880_dvbt2_stream)((data[0] >> 6) & 0x03);
	bbheader->is_single_input_stream = (data[0] >> 5) & 0x01;
	bbheader->is_constant_coding_modulation =
	    (data[0] >> 4) & 0x01;
	bbheader->issy_indicator = (data[0] >> 3) & 0x01;
	bbheader->null_packet_deletion = (data[0] >> 2) & 0x01;
	bbheader->ext = data[0] & 0x03;

	bbheader->input_stream_identifier = data[1];
	bbheader->plp_mode =
	    (data[3] & 0x01) ? CXD2880_DVBT2_PLP_MODE_HEM :
	    CXD2880_DVBT2_PLP_MODE_NM;
	bbheader->data_field_length = (data[4] << 8) | data[5];

	if (bbheader->plp_mode == CXD2880_DVBT2_PLP_MODE_NM) {
		bbheader->user_packet_length =
		    (data[6] << 8) | data[7];
		bbheader->sync_byte = data[8];
		bbheader->issy = 0;
	} else {
		bbheader->user_packet_length = 0;
		bbheader->sync_byte = 0;
		bbheader->issy =
		    (data[11] << 16) | (data[12] << 8) | data[13];
	}

	return 0;
}