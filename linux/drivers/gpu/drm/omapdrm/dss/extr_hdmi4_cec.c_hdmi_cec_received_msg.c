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
struct hdmi_core_data {int /*<<< orphan*/  base; int /*<<< orphan*/  adap; } ;
struct cec_msg {int len; int* msg; } ;

/* Variables and functions */
 int CEC_MAX_MSG_SIZE ; 
 unsigned int HDMI_CEC_RX_CMD_HEADER ; 
 unsigned int HDMI_CEC_RX_COMMAND ; 
 unsigned int HDMI_CEC_RX_CONTROL ; 
 unsigned int HDMI_CEC_RX_COUNT ; 
 unsigned int HDMI_CEC_RX_OPERAND ; 
 int /*<<< orphan*/  cec_received_msg (int /*<<< orphan*/ ,struct cec_msg*) ; 
 int hdmi_read_reg (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  hdmi_write_reg (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void hdmi_cec_received_msg(struct hdmi_core_data *core)
{
	u32 cnt = hdmi_read_reg(core->base, HDMI_CEC_RX_COUNT) & 0xff;

	/* While there are CEC frames in the FIFO */
	while (cnt & 0x70) {
		/* and the frame doesn't have an error */
		if (!(cnt & 0x80)) {
			struct cec_msg msg = {};
			unsigned int i;

			/* then read the message */
			msg.len = cnt & 0xf;
			if (msg.len > CEC_MAX_MSG_SIZE - 2)
				msg.len = CEC_MAX_MSG_SIZE - 2;
			msg.msg[0] = hdmi_read_reg(core->base,
						   HDMI_CEC_RX_CMD_HEADER);
			msg.msg[1] = hdmi_read_reg(core->base,
						   HDMI_CEC_RX_COMMAND);
			for (i = 0; i < msg.len; i++) {
				unsigned int reg = HDMI_CEC_RX_OPERAND + i * 4;

				msg.msg[2 + i] =
					hdmi_read_reg(core->base, reg);
			}
			msg.len += 2;
			cec_received_msg(core->adap, &msg);
		}
		/* Clear the current frame from the FIFO */
		hdmi_write_reg(core->base, HDMI_CEC_RX_CONTROL, 1);
		/* Wait until the current frame is cleared */
		while (hdmi_read_reg(core->base, HDMI_CEC_RX_CONTROL) & 1)
			udelay(1);
		/*
		 * Re-read the count register and loop to see if there are
		 * more messages in the FIFO.
		 */
		cnt = hdmi_read_reg(core->base, HDMI_CEC_RX_COUNT) & 0xff;
	}
}