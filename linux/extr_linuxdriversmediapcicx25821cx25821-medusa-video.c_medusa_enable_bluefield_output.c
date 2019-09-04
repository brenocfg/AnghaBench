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
 int OUT_CTRL1 ; 
 int OUT_CTRL_NS ; 
#define  VDEC_A 135 
#define  VDEC_B 134 
 int VDEC_B_OUT_CTRL1 ; 
 int VDEC_B_OUT_CTRL_NS ; 
#define  VDEC_C 133 
 int VDEC_C_OUT_CTRL1 ; 
 int VDEC_C_OUT_CTRL_NS ; 
#define  VDEC_D 132 
 int VDEC_D_OUT_CTRL1 ; 
 int VDEC_D_OUT_CTRL_NS ; 
#define  VDEC_E 131 
 int VDEC_E_OUT_CTRL1 ; 
 int VDEC_E_OUT_CTRL_NS ; 
#define  VDEC_F 130 
 int VDEC_F_OUT_CTRL1 ; 
 int VDEC_F_OUT_CTRL_NS ; 
#define  VDEC_G 129 
 int VDEC_G_OUT_CTRL1 ; 
 int VDEC_G_OUT_CTRL_NS ; 
#define  VDEC_H 128 
 int VDEC_H_OUT_CTRL1 ; 
 int VDEC_H_OUT_CTRL_NS ; 
 int cx25821_i2c_read (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  cx25821_i2c_write (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void medusa_enable_bluefield_output(struct cx25821_dev *dev, int channel,
					   int enable)
{
	u32 value = 0;
	u32 tmp = 0;
	int out_ctrl = OUT_CTRL1;
	int out_ctrl_ns = OUT_CTRL_NS;

	switch (channel) {
	default:
	case VDEC_A:
		break;
	case VDEC_B:
		out_ctrl = VDEC_B_OUT_CTRL1;
		out_ctrl_ns = VDEC_B_OUT_CTRL_NS;
		break;
	case VDEC_C:
		out_ctrl = VDEC_C_OUT_CTRL1;
		out_ctrl_ns = VDEC_C_OUT_CTRL_NS;
		break;
	case VDEC_D:
		out_ctrl = VDEC_D_OUT_CTRL1;
		out_ctrl_ns = VDEC_D_OUT_CTRL_NS;
		break;
	case VDEC_E:
		out_ctrl = VDEC_E_OUT_CTRL1;
		out_ctrl_ns = VDEC_E_OUT_CTRL_NS;
		return;
	case VDEC_F:
		out_ctrl = VDEC_F_OUT_CTRL1;
		out_ctrl_ns = VDEC_F_OUT_CTRL_NS;
		return;
	case VDEC_G:
		out_ctrl = VDEC_G_OUT_CTRL1;
		out_ctrl_ns = VDEC_G_OUT_CTRL_NS;
		return;
	case VDEC_H:
		out_ctrl = VDEC_H_OUT_CTRL1;
		out_ctrl_ns = VDEC_H_OUT_CTRL_NS;
		return;
	}

	value = cx25821_i2c_read(&dev->i2c_bus[0], out_ctrl, &tmp);
	value &= 0xFFFFFF7F;	/* clear BLUE_FIELD_EN */
	if (enable)
		value |= 0x00000080;	/* set BLUE_FIELD_EN */
	cx25821_i2c_write(&dev->i2c_bus[0], out_ctrl, value);

	value = cx25821_i2c_read(&dev->i2c_bus[0], out_ctrl_ns, &tmp);
	value &= 0xFFFFFF7F;
	if (enable)
		value |= 0x00000080;	/* set BLUE_FIELD_EN */
	cx25821_i2c_write(&dev->i2c_bus[0], out_ctrl_ns, value);
}