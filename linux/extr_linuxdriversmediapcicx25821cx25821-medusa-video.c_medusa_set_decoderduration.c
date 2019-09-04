#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct cx25821_dev {int /*<<< orphan*/ * i2c_bus; } ;

/* Variables and functions */
 int DISP_AB_CNT ; 
 int DISP_CD_CNT ; 
 int DISP_EF_CNT ; 
 int DISP_GH_CNT ; 
 int VDEC_A ; 
#define  VDEC_C 133 
#define  VDEC_D 132 
#define  VDEC_E 131 
#define  VDEC_F 130 
#define  VDEC_G 129 
#define  VDEC_H 128 
 int cx25821_i2c_read (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  cx25821_i2c_write (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void medusa_set_decoderduration(struct cx25821_dev *dev, int decoder,
				       int duration)
{
	u32 fld_cnt = 0;
	u32 tmp = 0;
	u32 disp_cnt_reg = DISP_AB_CNT;

	/* no support */
	if (decoder < VDEC_A || decoder > VDEC_H) {
		return;
	}

	switch (decoder) {
	default:
		break;
	case VDEC_C:
	case VDEC_D:
		disp_cnt_reg = DISP_CD_CNT;
		break;
	case VDEC_E:
	case VDEC_F:
		disp_cnt_reg = DISP_EF_CNT;
		break;
	case VDEC_G:
	case VDEC_H:
		disp_cnt_reg = DISP_GH_CNT;
		break;
	}

	/* update hardware */
	fld_cnt = cx25821_i2c_read(&dev->i2c_bus[0], disp_cnt_reg, &tmp);

	if (!(decoder % 2)) {	/* EVEN decoder */
		fld_cnt &= 0xFFFF0000;
		fld_cnt |= duration;
	} else {
		fld_cnt &= 0x0000FFFF;
		fld_cnt |= ((u32) duration) << 16;
	}

	cx25821_i2c_write(&dev->i2c_bus[0], disp_cnt_reg, fld_cnt);
}