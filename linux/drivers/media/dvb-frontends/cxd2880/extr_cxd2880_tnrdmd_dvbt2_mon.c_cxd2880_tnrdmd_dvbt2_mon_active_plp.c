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
typedef  int u8 ;
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; scalar_t__ sys; TYPE_1__* io; } ;
struct cxd2880_dvbt2_plp {int id; int type; int payload; int ff; int first_rf_idx; int first_frm_idx; int group_id; int plp_cr; int constell; int rot; int fec; int num_blocks_max; int frm_int; int til_len; int til_type; int in_band_a_flag; int rsvd; int in_band_b_flag; int plp_mode; int static_flag; int static_padding_flag; } ;
typedef  enum cxd2880_dvbt2_plp_type { ____Placeholder_cxd2880_dvbt2_plp_type } cxd2880_dvbt2_plp_type ;
typedef  enum cxd2880_dvbt2_plp_payload { ____Placeholder_cxd2880_dvbt2_plp_payload } cxd2880_dvbt2_plp_payload ;
typedef  enum cxd2880_dvbt2_plp_mode { ____Placeholder_cxd2880_dvbt2_plp_mode } cxd2880_dvbt2_plp_mode ;
typedef  enum cxd2880_dvbt2_plp_fec { ____Placeholder_cxd2880_dvbt2_plp_fec } cxd2880_dvbt2_plp_fec ;
typedef  enum cxd2880_dvbt2_plp_constell { ____Placeholder_cxd2880_dvbt2_plp_constell } cxd2880_dvbt2_plp_constell ;
typedef  enum cxd2880_dvbt2_plp_code_rate { ____Placeholder_cxd2880_dvbt2_plp_code_rate } cxd2880_dvbt2_plp_code_rate ;
typedef  enum cxd2880_dvbt2_plp_btype { ____Placeholder_cxd2880_dvbt2_plp_btype } cxd2880_dvbt2_plp_btype ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_4__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* read_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 scalar_t__ CXD2880_DTV_SYS_DVBT2 ; 
 int CXD2880_DVBT2_PLP_COMMON ; 
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

int cxd2880_tnrdmd_dvbt2_mon_active_plp(struct cxd2880_tnrdmd
					*tnr_dmd,
					enum
					cxd2880_dvbt2_plp_btype
					type,
					struct cxd2880_dvbt2_plp
					*plp_info)
{
	u8 data[20];
	u8 addr = 0;
	u8 index = 0;
	u8 l1_post_ok = 0;
	int ret;

	if (!tnr_dmd || !plp_info)
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

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x86, &l1_post_ok, 1);
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	if (!l1_post_ok) {
		slvt_unfreeze_reg(tnr_dmd);
		return -EAGAIN;
	}

	if (type == CXD2880_DVBT2_PLP_COMMON)
		addr = 0xa9;
	else
		addr = 0x96;

	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     addr, data, sizeof(data));
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	slvt_unfreeze_reg(tnr_dmd);

	if (type == CXD2880_DVBT2_PLP_COMMON && !data[13])
		return -EAGAIN;

	plp_info->id = data[index++];
	plp_info->type =
	    (enum cxd2880_dvbt2_plp_type)(data[index++] & 0x07);
	plp_info->payload =
	    (enum cxd2880_dvbt2_plp_payload)(data[index++] & 0x1f);
	plp_info->ff = data[index++] & 0x01;
	plp_info->first_rf_idx = data[index++] & 0x07;
	plp_info->first_frm_idx = data[index++];
	plp_info->group_id = data[index++];
	plp_info->plp_cr =
	    (enum cxd2880_dvbt2_plp_code_rate)(data[index++] & 0x07);
	plp_info->constell =
	    (enum cxd2880_dvbt2_plp_constell)(data[index++] & 0x07);
	plp_info->rot = data[index++] & 0x01;
	plp_info->fec =
	    (enum cxd2880_dvbt2_plp_fec)(data[index++] & 0x03);
	plp_info->num_blocks_max = (data[index++] & 0x03) << 8;
	plp_info->num_blocks_max |= data[index++];
	plp_info->frm_int = data[index++];
	plp_info->til_len = data[index++];
	plp_info->til_type = data[index++] & 0x01;

	plp_info->in_band_a_flag = data[index++] & 0x01;
	plp_info->rsvd = data[index++] << 8;
	plp_info->rsvd |= data[index++];

	plp_info->in_band_b_flag =
	    (plp_info->rsvd & 0x8000) >> 15;
	plp_info->plp_mode =
	    (enum cxd2880_dvbt2_plp_mode)((plp_info->rsvd & 0x000c) >> 2);
	plp_info->static_flag = (plp_info->rsvd & 0x0002) >> 1;
	plp_info->static_padding_flag = plp_info->rsvd & 0x0001;
	plp_info->rsvd = (plp_info->rsvd & 0x7ff0) >> 4;

	return 0;
}