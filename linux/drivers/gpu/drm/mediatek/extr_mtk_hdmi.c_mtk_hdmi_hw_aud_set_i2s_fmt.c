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
struct mtk_hdmi {int dummy; } ;
typedef  enum hdmi_aud_i2s_fmt { ____Placeholder_hdmi_aud_i2s_fmt } hdmi_aud_i2s_fmt ;

/* Variables and functions */
 int CFG0_I2S_MODE_I2S ; 
 int CFG0_I2S_MODE_LTJ ; 
 int CFG0_I2S_MODE_MASK ; 
 int CFG0_I2S_MODE_RTJ ; 
 int CFG0_W_LENGTH_16BIT ; 
 int CFG0_W_LENGTH_24BIT ; 
 int CFG0_W_LENGTH_MASK ; 
 int /*<<< orphan*/  GRL_CFG0 ; 
#define  HDMI_I2S_MODE_I2S_16BIT 133 
#define  HDMI_I2S_MODE_I2S_24BIT 132 
#define  HDMI_I2S_MODE_LJT_16BIT 131 
#define  HDMI_I2S_MODE_LJT_24BIT 130 
#define  HDMI_I2S_MODE_RJT_16BIT 129 
#define  HDMI_I2S_MODE_RJT_24BIT 128 
 int mtk_hdmi_read (struct mtk_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hdmi_write (struct mtk_hdmi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mtk_hdmi_hw_aud_set_i2s_fmt(struct mtk_hdmi *hdmi,
					enum hdmi_aud_i2s_fmt i2s_fmt)
{
	u32 val;

	val = mtk_hdmi_read(hdmi, GRL_CFG0);
	val &= ~(CFG0_W_LENGTH_MASK | CFG0_I2S_MODE_MASK);

	switch (i2s_fmt) {
	case HDMI_I2S_MODE_RJT_24BIT:
		val |= CFG0_I2S_MODE_RTJ | CFG0_W_LENGTH_24BIT;
		break;
	case HDMI_I2S_MODE_RJT_16BIT:
		val |= CFG0_I2S_MODE_RTJ | CFG0_W_LENGTH_16BIT;
		break;
	case HDMI_I2S_MODE_LJT_24BIT:
	default:
		val |= CFG0_I2S_MODE_LTJ | CFG0_W_LENGTH_24BIT;
		break;
	case HDMI_I2S_MODE_LJT_16BIT:
		val |= CFG0_I2S_MODE_LTJ | CFG0_W_LENGTH_16BIT;
		break;
	case HDMI_I2S_MODE_I2S_24BIT:
		val |= CFG0_I2S_MODE_I2S | CFG0_W_LENGTH_24BIT;
		break;
	case HDMI_I2S_MODE_I2S_16BIT:
		val |= CFG0_I2S_MODE_I2S | CFG0_W_LENGTH_16BIT;
		break;
	}
	mtk_hdmi_write(hdmi, GRL_CFG0, val);
}