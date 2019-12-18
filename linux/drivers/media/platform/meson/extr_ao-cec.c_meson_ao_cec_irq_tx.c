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
typedef  int u8 ;
struct meson_ao_cec_device {int /*<<< orphan*/  adap; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ CEC_INTR_CLR_REG ; 
 int /*<<< orphan*/  CEC_INTR_TX ; 
 int /*<<< orphan*/  CEC_TX_MSG_CMD ; 
 int /*<<< orphan*/  CEC_TX_MSG_STATUS ; 
 unsigned long CEC_TX_STATUS_ARB_LOST ; 
 unsigned long CEC_TX_STATUS_ERROR ; 
 unsigned long CEC_TX_STATUS_LOW_DRIVE ; 
 unsigned long CEC_TX_STATUS_NACK ; 
 unsigned long CEC_TX_STATUS_OK ; 
#define  TX_BUSY 131 
#define  TX_DONE 130 
#define  TX_ERROR 129 
#define  TX_IDLE 128 
 int /*<<< orphan*/  TX_NO_OP ; 
 int /*<<< orphan*/  cec_transmit_attempt_done (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  meson_ao_cec_read (struct meson_ao_cec_device*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  meson_ao_cec_write (struct meson_ao_cec_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_ao_cec_irq_tx(struct meson_ao_cec_device *ao_cec)
{
	unsigned long tx_status = 0;
	u8 stat;
	int ret = 0;

	meson_ao_cec_read(ao_cec, CEC_TX_MSG_STATUS, &stat, &ret);
	if (ret)
		goto tx_reg_err;

	switch (stat) {
	case TX_DONE:
		tx_status = CEC_TX_STATUS_OK;
		break;

	case TX_BUSY:
		tx_status = CEC_TX_STATUS_ARB_LOST;
		break;

	case TX_IDLE:
		tx_status = CEC_TX_STATUS_LOW_DRIVE;
		break;

	case TX_ERROR:
	default:
		tx_status = CEC_TX_STATUS_NACK;
		break;
	}

	/* Clear Interruption */
	writel_relaxed(CEC_INTR_TX, ao_cec->base + CEC_INTR_CLR_REG);

	/* Stop TX */
	meson_ao_cec_write(ao_cec, CEC_TX_MSG_CMD, TX_NO_OP, &ret);
	if (ret)
		goto tx_reg_err;

	cec_transmit_attempt_done(ao_cec->adap, tx_status);
	return;

tx_reg_err:
	cec_transmit_attempt_done(ao_cec->adap, CEC_TX_STATUS_ERROR);
}