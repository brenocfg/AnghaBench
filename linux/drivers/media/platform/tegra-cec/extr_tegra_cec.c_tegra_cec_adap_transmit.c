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
typedef  scalar_t__ u32 ;
struct tegra_cec {unsigned int tx_buf_cnt; scalar_t__* tx_buf; scalar_t__ tx_buf_cur; } ;
struct cec_msg {unsigned int len; scalar_t__* msg; } ;
struct cec_adapter {struct tegra_cec* priv; } ;

/* Variables and functions */
 scalar_t__ CEC_SIGNAL_FREE_TIME_RETRY ; 
 int /*<<< orphan*/  TEGRA_CEC_INT_MASK ; 
 scalar_t__ TEGRA_CEC_INT_MASK_TX_REGISTER_EMPTY ; 
 scalar_t__ TEGRA_CEC_TX_REG_BCAST ; 
 scalar_t__ TEGRA_CEC_TX_REG_EOM ; 
 scalar_t__ TEGRA_CEC_TX_REG_RETRY ; 
 scalar_t__ TEGRA_CEC_TX_REG_START_BIT ; 
 scalar_t__ cec_msg_is_broadcast (struct cec_msg*) ; 
 scalar_t__ cec_read (struct tegra_cec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_write (struct tegra_cec*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int tegra_cec_adap_transmit(struct cec_adapter *adap, u8 attempts,
				   u32 signal_free_time_ms, struct cec_msg *msg)
{
	bool retry_xfer = signal_free_time_ms == CEC_SIGNAL_FREE_TIME_RETRY;
	struct tegra_cec *cec = adap->priv;
	unsigned int i;
	u32 mode = 0;
	u32 mask;

	if (cec_msg_is_broadcast(msg))
		mode = TEGRA_CEC_TX_REG_BCAST;

	cec->tx_buf_cur = 0;
	cec->tx_buf_cnt = msg->len;

	for (i = 0; i < msg->len; i++) {
		cec->tx_buf[i] = mode | msg->msg[i];
		if (i == 0)
			cec->tx_buf[i] |= TEGRA_CEC_TX_REG_START_BIT;
		if (i == msg->len - 1)
			cec->tx_buf[i] |= TEGRA_CEC_TX_REG_EOM;
		if (i == 0 && retry_xfer)
			cec->tx_buf[i] |= TEGRA_CEC_TX_REG_RETRY;
	}

	mask = cec_read(cec, TEGRA_CEC_INT_MASK);
	cec_write(cec, TEGRA_CEC_INT_MASK,
		  mask | TEGRA_CEC_INT_MASK_TX_REGISTER_EMPTY);

	return 0;
}