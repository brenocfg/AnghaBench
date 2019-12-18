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
struct meson_ao_cec_g12a_device {int /*<<< orphan*/  regmap_cec; int /*<<< orphan*/  adap; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CECB_CTRL ; 
 int CECB_CTRL_SEND ; 
 int CECB_CTRL_TYPE ; 
 int CECB_INTR_ARB_LOSS ; 
 int /*<<< orphan*/  CECB_INTR_CLR_REG ; 
 int CECB_INTR_DONE ; 
 int CECB_INTR_EOM ; 
 int CECB_INTR_FOLLOWER_ERR ; 
 int CECB_INTR_INITIATOR_ERR ; 
 int CECB_INTR_NACK ; 
 int /*<<< orphan*/  CECB_INTR_STAT_REG ; 
 int /*<<< orphan*/  CECB_LOCK_BUF ; 
 int /*<<< orphan*/  CECB_TX_CNT ; 
 int /*<<< orphan*/  CEC_TX_STATUS_ARB_LOST ; 
 int /*<<< orphan*/  CEC_TX_STATUS_ERROR ; 
 int /*<<< orphan*/  CEC_TX_STATUS_NACK ; 
 int /*<<< orphan*/  CEC_TX_STATUS_OK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  cec_transmit_attempt_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_ao_cec_g12a_irq_rx (struct meson_ao_cec_g12a_device*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t meson_ao_cec_g12a_irq_thread(int irq, void *data)
{
	struct meson_ao_cec_g12a_device *ao_cec = data;
	u32 stat;

	regmap_read(ao_cec->regmap, CECB_INTR_STAT_REG, &stat);
	regmap_write(ao_cec->regmap, CECB_INTR_CLR_REG, stat);

	if (stat & CECB_INTR_DONE)
		cec_transmit_attempt_done(ao_cec->adap, CEC_TX_STATUS_OK);

	if (stat & CECB_INTR_EOM)
		meson_ao_cec_g12a_irq_rx(ao_cec);

	if (stat & CECB_INTR_NACK)
		cec_transmit_attempt_done(ao_cec->adap, CEC_TX_STATUS_NACK);

	if (stat & CECB_INTR_ARB_LOSS) {
		regmap_write(ao_cec->regmap_cec, CECB_TX_CNT, 0);
		regmap_update_bits(ao_cec->regmap_cec, CECB_CTRL,
				   CECB_CTRL_SEND | CECB_CTRL_TYPE, 0);
		cec_transmit_attempt_done(ao_cec->adap, CEC_TX_STATUS_ARB_LOST);
	}

	/* Initiator reports an error on the CEC bus */
	if (stat & CECB_INTR_INITIATOR_ERR)
		cec_transmit_attempt_done(ao_cec->adap, CEC_TX_STATUS_ERROR);

	/* Follower reports a receive error, just reset RX buffer */
	if (stat & CECB_INTR_FOLLOWER_ERR)
		regmap_write(ao_cec->regmap_cec, CECB_LOCK_BUF, 0);

	return IRQ_HANDLED;
}