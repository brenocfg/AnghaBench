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
typedef  int u32 ;
struct cxd2880_tnrdmd {scalar_t__ state; scalar_t__ sys; int bandwidth; TYPE_1__* io; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_3__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* read_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
#define  CXD2880_DTV_BW_1_7_MHZ 132 
#define  CXD2880_DTV_BW_5_MHZ 131 
#define  CXD2880_DTV_BW_6_MHZ 130 
#define  CXD2880_DTV_BW_7_MHZ 129 
#define  CXD2880_DTV_BW_8_MHZ 128 
 scalar_t__ CXD2880_DTV_SYS_DVBT2 ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int cxd2880_convert2s_complement (int,int) ; 
 int cxd2880_tnrdmd_dvbt2_mon_sync_stat (struct cxd2880_tnrdmd*,int*,int*,int*) ; 
 int slvt_freeze_reg (struct cxd2880_tnrdmd*) ; 
 int /*<<< orphan*/  slvt_unfreeze_reg (struct cxd2880_tnrdmd*) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 

int cxd2880_tnrdmd_dvbt2_mon_carrier_offset(struct cxd2880_tnrdmd
					    *tnr_dmd, int *offset)
{
	u8 data[4];
	u32 ctl_val = 0;
	u8 sync_state = 0;
	u8 ts_lock = 0;
	u8 unlock_detected = 0;
	int ret;

	if (!tnr_dmd || !offset)
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
		return -EAGAIN;
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
				     0x30, data, sizeof(data));
	if (ret) {
		slvt_unfreeze_reg(tnr_dmd);
		return ret;
	}

	slvt_unfreeze_reg(tnr_dmd);

	ctl_val =
	    ((data[0] & 0x0f) << 24) | (data[1] << 16) | (data[2] << 8)
	    | (data[3]);
	*offset = cxd2880_convert2s_complement(ctl_val, 28);

	switch (tnr_dmd->bandwidth) {
	case CXD2880_DTV_BW_1_7_MHZ:
		*offset = -1 * ((*offset) / 582);
		break;
	case CXD2880_DTV_BW_5_MHZ:
	case CXD2880_DTV_BW_6_MHZ:
	case CXD2880_DTV_BW_7_MHZ:
	case CXD2880_DTV_BW_8_MHZ:
		*offset = -1 * ((*offset) * tnr_dmd->bandwidth / 940);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}