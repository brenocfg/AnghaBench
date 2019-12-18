#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {struct device* parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;
struct mtk_hdmi_ddc {TYPE_2__ adap; } ;
struct i2c_msg {int addr; int* buf; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDCM_ACK_MASK ; 
 int /*<<< orphan*/  DDCM_ACK_OFFSET ; 
 int /*<<< orphan*/  DDCM_DATA0 ; 
 int /*<<< orphan*/  DDCM_DATA1 ; 
 int /*<<< orphan*/  DDCM_PGLEN_MASK ; 
 int DDCM_PGLEN_OFFSET ; 
 int /*<<< orphan*/  DDCM_START ; 
 int /*<<< orphan*/  DDCM_WRITE_DATA ; 
 int /*<<< orphan*/  DDC_DDCMCTL1 ; 
 int /*<<< orphan*/  DDC_DDCMD0 ; 
 int EIO ; 
 int /*<<< orphan*/  ddcm_trigger_mode (struct mtk_hdmi_ddc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int sif_read_mask (struct mtk_hdmi_ddc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sif_write_mask (struct mtk_hdmi_ddc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mtk_hdmi_ddc_write_msg(struct mtk_hdmi_ddc *ddc, struct i2c_msg *msg)
{
	struct device *dev = ddc->adap.dev.parent;
	u32 ack;

	ddcm_trigger_mode(ddc, DDCM_START);
	sif_write_mask(ddc, DDC_DDCMD0, DDCM_DATA0, 0, msg->addr << 1);
	sif_write_mask(ddc, DDC_DDCMD0, DDCM_DATA1, 8, msg->buf[0]);
	sif_write_mask(ddc, DDC_DDCMCTL1, DDCM_PGLEN_MASK, DDCM_PGLEN_OFFSET,
		       0x1);
	ddcm_trigger_mode(ddc, DDCM_WRITE_DATA);

	ack = sif_read_mask(ddc, DDC_DDCMCTL1, DDCM_ACK_MASK, DDCM_ACK_OFFSET);
	dev_dbg(dev, "ack = %d\n", ack);

	if (ack != 0x03) {
		dev_err(dev, "i2c ack err!\n");
		return -EIO;
	}

	return 0;
}