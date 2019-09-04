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
struct cxd2880_dvbt2_l1post {int sub_slices_per_frame; int num_plps; int num_aux; int aux_cfg_rfu; int rf_idx; int freq; int fef_type; int fef_length; int fef_intvl; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_3__ {int (* write_reg ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;int (* read_regs ) (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ;} ;

/* Variables and functions */
 scalar_t__ CXD2880_DTV_SYS_DVBT2 ; 
 int /*<<< orphan*/  CXD2880_IO_TGT_DMD ; 
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SUB ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int) ; 

int cxd2880_tnrdmd_dvbt2_mon_l1_post(struct cxd2880_tnrdmd
				     *tnr_dmd,
				     struct cxd2880_dvbt2_l1post
				     *l1_post)
{
	u8 data[16];
	int ret;

	if (!tnr_dmd || !l1_post)
		return -EINVAL;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	if (tnr_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		return -EINVAL;

	ret = tnr_dmd->io->write_reg(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (ret)
		return ret;

	ret = tnr_dmd->io->read_regs(tnr_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x86, data, sizeof(data));
	if (ret)
		return ret;

	if (!(data[0] & 0x01))
		return -EAGAIN;

	l1_post->sub_slices_per_frame = (data[1] & 0x7f) << 8;
	l1_post->sub_slices_per_frame |= data[2];
	l1_post->num_plps = data[3];
	l1_post->num_aux = data[4] & 0x0f;
	l1_post->aux_cfg_rfu = data[5];
	l1_post->rf_idx = data[6] & 0x07;
	l1_post->freq = data[7] << 24;
	l1_post->freq |= data[8] << 16;
	l1_post->freq |= data[9] << 8;
	l1_post->freq |= data[10];
	l1_post->fef_type = data[11] & 0x0f;
	l1_post->fef_length = data[12] << 16;
	l1_post->fef_length |= data[13] << 8;
	l1_post->fef_length |= data[14];
	l1_post->fef_intvl = data[15];

	return 0;
}