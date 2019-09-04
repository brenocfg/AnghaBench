#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mtk_hdmi_ddc {int dummy; } ;
struct i2c_msg {int flags; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {struct device* parent; } ;
struct i2c_adapter {TYPE_1__ dev; struct mtk_hdmi_ddc* algo_data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDCM_CLK_DIV_MASK ; 
 int /*<<< orphan*/  DDCM_CLK_DIV_OFFSET ; 
 int /*<<< orphan*/  DDCM_ODRAIN ; 
 int /*<<< orphan*/  DDCM_SCL_STRECH ; 
 int /*<<< orphan*/  DDCM_SM0EN ; 
 int /*<<< orphan*/  DDCM_STOP ; 
 int /*<<< orphan*/  DDCM_TRI ; 
 int /*<<< orphan*/  DDC_DDCMCTL0 ; 
 int /*<<< orphan*/  DDC_DDCMCTL1 ; 
 int EBUSY ; 
 int EINVAL ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  SIF1_CLOK ; 
 int /*<<< orphan*/  ddcm_trigger_mode (struct mtk_hdmi_ddc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int mtk_hdmi_ddc_read_msg (struct mtk_hdmi_ddc*,struct i2c_msg*) ; 
 int mtk_hdmi_ddc_write_msg (struct mtk_hdmi_ddc*,struct i2c_msg*) ; 
 scalar_t__ sif_bit_is_set (struct mtk_hdmi_ddc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sif_clr_bit (struct mtk_hdmi_ddc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sif_set_bit (struct mtk_hdmi_ddc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sif_write_mask (struct mtk_hdmi_ddc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_hdmi_ddc_xfer(struct i2c_adapter *adapter,
			     struct i2c_msg *msgs, int num)
{
	struct mtk_hdmi_ddc *ddc = adapter->algo_data;
	struct device *dev = adapter->dev.parent;
	int ret;
	int i;

	if (!ddc) {
		dev_err(dev, "invalid arguments\n");
		return -EINVAL;
	}

	sif_set_bit(ddc, DDC_DDCMCTL0, DDCM_SCL_STRECH);
	sif_set_bit(ddc, DDC_DDCMCTL0, DDCM_SM0EN);
	sif_clr_bit(ddc, DDC_DDCMCTL0, DDCM_ODRAIN);

	if (sif_bit_is_set(ddc, DDC_DDCMCTL1, DDCM_TRI)) {
		dev_err(dev, "ddc line is busy!\n");
		return -EBUSY;
	}

	sif_write_mask(ddc, DDC_DDCMCTL0, DDCM_CLK_DIV_MASK,
		       DDCM_CLK_DIV_OFFSET, SIF1_CLOK);

	for (i = 0; i < num; i++) {
		struct i2c_msg *msg = &msgs[i];

		dev_dbg(dev, "i2c msg, adr:0x%x, flags:%d, len :0x%x\n",
			msg->addr, msg->flags, msg->len);

		if (msg->flags & I2C_M_RD)
			ret = mtk_hdmi_ddc_read_msg(ddc, msg);
		else
			ret = mtk_hdmi_ddc_write_msg(ddc, msg);
		if (ret < 0)
			goto xfer_end;
	}

	ddcm_trigger_mode(ddc, DDCM_STOP);

	return i;

xfer_end:
	ddcm_trigger_mode(ddc, DDCM_STOP);
	dev_err(dev, "ddc failed!\n");
	return ret;
}