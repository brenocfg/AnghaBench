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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct dw_hdmi_cec {int dummy; } ;
struct cec_msg {unsigned int len; unsigned int* msg; } ;
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 unsigned int CEC_CTRL_IMMED ; 
 unsigned int CEC_CTRL_NORMAL ; 
 unsigned int CEC_CTRL_RETRY ; 
 unsigned int CEC_CTRL_START ; 
#define  CEC_SIGNAL_FREE_TIME_NEW_INITIATOR 130 
#define  CEC_SIGNAL_FREE_TIME_NEXT_XFER 129 
#define  CEC_SIGNAL_FREE_TIME_RETRY 128 
 scalar_t__ HDMI_CEC_CTRL ; 
 scalar_t__ HDMI_CEC_TX_CNT ; 
 scalar_t__ HDMI_CEC_TX_DATA0 ; 
 struct dw_hdmi_cec* cec_get_drvdata (struct cec_adapter*) ; 
 int /*<<< orphan*/  dw_hdmi_write (struct dw_hdmi_cec*,unsigned int,scalar_t__) ; 

__attribute__((used)) static int dw_hdmi_cec_transmit(struct cec_adapter *adap, u8 attempts,
				u32 signal_free_time, struct cec_msg *msg)
{
	struct dw_hdmi_cec *cec = cec_get_drvdata(adap);
	unsigned int i, ctrl;

	switch (signal_free_time) {
	case CEC_SIGNAL_FREE_TIME_RETRY:
		ctrl = CEC_CTRL_RETRY;
		break;
	case CEC_SIGNAL_FREE_TIME_NEW_INITIATOR:
	default:
		ctrl = CEC_CTRL_NORMAL;
		break;
	case CEC_SIGNAL_FREE_TIME_NEXT_XFER:
		ctrl = CEC_CTRL_IMMED;
		break;
	}

	for (i = 0; i < msg->len; i++)
		dw_hdmi_write(cec, msg->msg[i], HDMI_CEC_TX_DATA0 + i);

	dw_hdmi_write(cec, msg->len, HDMI_CEC_TX_CNT);
	dw_hdmi_write(cec, ctrl | CEC_CTRL_START, HDMI_CEC_CTRL);

	return 0;
}