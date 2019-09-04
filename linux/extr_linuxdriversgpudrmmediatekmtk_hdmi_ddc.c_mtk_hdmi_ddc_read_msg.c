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
struct i2c_msg {int addr; int len; void** buf; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DDCM_ACK_MASK ; 
 int DDCM_ACK_OFFSET ; 
 int DDCM_PGLEN_MASK ; 
 int /*<<< orphan*/  DDCM_PGLEN_OFFSET ; 
 int /*<<< orphan*/  DDCM_READ_DATA_ACK ; 
 int /*<<< orphan*/  DDCM_READ_DATA_NO_ACK ; 
 int /*<<< orphan*/  DDCM_START ; 
 int /*<<< orphan*/  DDCM_WRITE_DATA ; 
 int DDC_DDCMCTL1 ; 
 int DDC_DDCMD0 ; 
 int DDC_DDCMD1 ; 
 int ENXIO ; 
 int /*<<< orphan*/  ddcm_trigger_mode (struct mtk_hdmi_ddc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* sif_read_mask (struct mtk_hdmi_ddc*,int,int,int) ; 
 int /*<<< orphan*/  sif_write_mask (struct mtk_hdmi_ddc*,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mtk_hdmi_ddc_read_msg(struct mtk_hdmi_ddc *ddc, struct i2c_msg *msg)
{
	struct device *dev = ddc->adap.dev.parent;
	u32 remain_count, ack_count, ack_final, read_count, temp_count;
	u32 index = 0;
	u32 ack;
	int i;

	ddcm_trigger_mode(ddc, DDCM_START);
	sif_write_mask(ddc, DDC_DDCMD0, 0xff, 0, (msg->addr << 1) | 0x01);
	sif_write_mask(ddc, DDC_DDCMCTL1, DDCM_PGLEN_MASK, DDCM_PGLEN_OFFSET,
		       0x00);
	ddcm_trigger_mode(ddc, DDCM_WRITE_DATA);
	ack = sif_read_mask(ddc, DDC_DDCMCTL1, DDCM_ACK_MASK, DDCM_ACK_OFFSET);
	dev_dbg(dev, "ack = 0x%x\n", ack);
	if (ack != 0x01) {
		dev_err(dev, "i2c ack err!\n");
		return -ENXIO;
	}

	remain_count = msg->len;
	ack_count = (msg->len - 1) / 8;
	ack_final = 0;

	while (remain_count > 0) {
		if (ack_count > 0) {
			read_count = 8;
			ack_final = 0;
			ack_count--;
		} else {
			read_count = remain_count;
			ack_final = 1;
		}

		sif_write_mask(ddc, DDC_DDCMCTL1, DDCM_PGLEN_MASK,
			       DDCM_PGLEN_OFFSET, read_count - 1);
		ddcm_trigger_mode(ddc, (ack_final == 1) ?
				  DDCM_READ_DATA_NO_ACK :
				  DDCM_READ_DATA_ACK);

		ack = sif_read_mask(ddc, DDC_DDCMCTL1, DDCM_ACK_MASK,
				    DDCM_ACK_OFFSET);
		temp_count = 0;
		while (((ack & (1 << temp_count)) != 0) && (temp_count < 8))
			temp_count++;
		if (((ack_final == 1) && (temp_count != (read_count - 1))) ||
		    ((ack_final == 0) && (temp_count != read_count))) {
			dev_err(dev, "Address NACK! ACK(0x%x)\n", ack);
			break;
		}

		for (i = read_count; i >= 1; i--) {
			int shift;
			int offset;

			if (i > 4) {
				offset = DDC_DDCMD1;
				shift = (i - 5) * 8;
			} else {
				offset = DDC_DDCMD0;
				shift = (i - 1) * 8;
			}

			msg->buf[index + i - 1] = sif_read_mask(ddc, offset,
								0xff << shift,
								shift);
		}

		remain_count -= read_count;
		index += read_count;
	}

	return 0;
}