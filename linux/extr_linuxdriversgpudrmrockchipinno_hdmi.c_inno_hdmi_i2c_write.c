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
struct inno_hdmi {TYPE_1__* i2c; } ;
struct i2c_msg {int len; scalar_t__ addr; int* buf; } ;
struct TYPE_2__ {int segment_addr; int ddc_addr; int /*<<< orphan*/  cmp; } ;

/* Variables and functions */
 scalar_t__ DDC_ADDR ; 
 scalar_t__ DDC_SEGMENT_ADDR ; 
 int EINVAL ; 
 int /*<<< orphan*/  HDMI_EDID_FIFO_OFFSET ; 
 int /*<<< orphan*/  HDMI_EDID_SEGMENT_POINTER ; 
 int /*<<< orphan*/  HDMI_EDID_WORD_ADDR ; 
 int /*<<< orphan*/  hdmi_writeb (struct inno_hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int inno_hdmi_i2c_write(struct inno_hdmi *hdmi, struct i2c_msg *msgs)
{
	/*
	 * The DDC module only support read EDID message, so
	 * we assume that each word write to this i2c adapter
	 * should be the offset of EDID word address.
	 */
	if ((msgs->len != 1) ||
	    ((msgs->addr != DDC_ADDR) && (msgs->addr != DDC_SEGMENT_ADDR)))
		return -EINVAL;

	reinit_completion(&hdmi->i2c->cmp);

	if (msgs->addr == DDC_SEGMENT_ADDR)
		hdmi->i2c->segment_addr = msgs->buf[0];
	if (msgs->addr == DDC_ADDR)
		hdmi->i2c->ddc_addr = msgs->buf[0];

	/* Set edid fifo first addr */
	hdmi_writeb(hdmi, HDMI_EDID_FIFO_OFFSET, 0x00);

	/* Set edid word address 0x00/0x80 */
	hdmi_writeb(hdmi, HDMI_EDID_WORD_ADDR, hdmi->i2c->ddc_addr);

	/* Set edid segment pointer */
	hdmi_writeb(hdmi, HDMI_EDID_SEGMENT_POINTER, hdmi->i2c->segment_addr);

	return 0;
}