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
typedef  int u8 ;
struct TYPE_2__ {int len; int* msg; } ;
struct meson_ao_cec_device {scalar_t__ base; TYPE_1__ rx_msg; int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 scalar_t__ CEC_INTR_CLR_REG ; 
 int /*<<< orphan*/  CEC_INTR_RX ; 
 int CEC_MAX_MSG_SIZE ; 
 int /*<<< orphan*/  CEC_RX_CLEAR_BUF ; 
 scalar_t__ CEC_RX_MSG_0_HEADER ; 
 int /*<<< orphan*/  CEC_RX_MSG_CMD ; 
 scalar_t__ CEC_RX_MSG_LENGTH ; 
 scalar_t__ CEC_RX_MSG_STATUS ; 
 scalar_t__ CEC_RX_NUM_MSG ; 
 int /*<<< orphan*/  CLEAR_START ; 
 int /*<<< orphan*/  CLEAR_STOP ; 
 int /*<<< orphan*/  RX_ACK_CURRENT ; 
 int RX_DONE ; 
 int /*<<< orphan*/  RX_NO_OP ; 
 int /*<<< orphan*/  cec_received_msg (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  meson_ao_cec_read (struct meson_ao_cec_device*,scalar_t__,int*,int*) ; 
 int /*<<< orphan*/  meson_ao_cec_write (struct meson_ao_cec_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_ao_cec_irq_rx(struct meson_ao_cec_device *ao_cec)
{
	int i, ret = 0;
	u8 reg;

	meson_ao_cec_read(ao_cec, CEC_RX_MSG_STATUS, &reg, &ret);
	if (reg != RX_DONE)
		goto rx_out;

	meson_ao_cec_read(ao_cec, CEC_RX_NUM_MSG, &reg, &ret);
	if (reg != 1)
		goto rx_out;

	meson_ao_cec_read(ao_cec, CEC_RX_MSG_LENGTH, &reg, &ret);

	ao_cec->rx_msg.len = reg + 1;
	if (ao_cec->rx_msg.len > CEC_MAX_MSG_SIZE)
		ao_cec->rx_msg.len = CEC_MAX_MSG_SIZE;

	for (i = 0; i < ao_cec->rx_msg.len; i++) {
		u8 byte;

		meson_ao_cec_read(ao_cec, CEC_RX_MSG_0_HEADER + i, &byte, &ret);

		ao_cec->rx_msg.msg[i] = byte;
	}

	if (ret)
		goto rx_out;

	cec_received_msg(ao_cec->adap, &ao_cec->rx_msg);

rx_out:
	/* Clear Interruption */
	writel_relaxed(CEC_INTR_RX, ao_cec->base + CEC_INTR_CLR_REG);

	/* Ack RX message */
	meson_ao_cec_write(ao_cec, CEC_RX_MSG_CMD, RX_ACK_CURRENT, &ret);
	meson_ao_cec_write(ao_cec, CEC_RX_MSG_CMD, RX_NO_OP, &ret);

	/* Clear RX buffer */
	meson_ao_cec_write(ao_cec, CEC_RX_CLEAR_BUF, CLEAR_START, &ret);
	meson_ao_cec_write(ao_cec, CEC_RX_CLEAR_BUF, CLEAR_STOP, &ret);
}