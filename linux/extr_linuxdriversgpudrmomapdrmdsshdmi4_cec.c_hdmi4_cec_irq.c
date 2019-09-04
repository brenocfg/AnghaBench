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

/* Variables and functions */
 int CEC_TX_STATUS_MAX_RETRIES ; 
 int CEC_TX_STATUS_NACK ; 
 int CEC_TX_STATUS_OK ; 
 int /*<<< orphan*/  HDMI_CEC_DBG_3 ; 
 int /*<<< orphan*/  HDMI_CEC_INT_STATUS_0 ; 
 int /*<<< orphan*/  HDMI_CEC_INT_STATUS_1 ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  cec_transmit_done (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_cec_received_msg (struct hdmi_core_data*) ; 
 int hdmi_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void hdmi4_cec_irq(struct hdmi_core_data *core)
{
	u32 stat0 = hdmi_read_reg(core->base, HDMI_CEC_INT_STATUS_0);
	u32 stat1 = hdmi_read_reg(core->base, HDMI_CEC_INT_STATUS_1);

	hdmi_write_reg(core->base, HDMI_CEC_INT_STATUS_0, stat0);
	hdmi_write_reg(core->base, HDMI_CEC_INT_STATUS_1, stat1);

	if (stat0 & 0x20) {
		cec_transmit_done(core->adap, CEC_TX_STATUS_OK,
				  0, 0, 0, 0);
		REG_FLD_MOD(core->base, HDMI_CEC_DBG_3, 0x1, 7, 7);
	} else if (stat1 & 0x02) {
		u32 dbg3 = hdmi_read_reg(core->base, HDMI_CEC_DBG_3);

		cec_transmit_done(core->adap,
				  CEC_TX_STATUS_NACK |
				  CEC_TX_STATUS_MAX_RETRIES,
				  0, (dbg3 >> 4) & 7, 0, 0);
		REG_FLD_MOD(core->base, HDMI_CEC_DBG_3, 0x1, 7, 7);
	}
	if (stat0 & 0x02)
		hdmi_cec_received_msg(core);
}