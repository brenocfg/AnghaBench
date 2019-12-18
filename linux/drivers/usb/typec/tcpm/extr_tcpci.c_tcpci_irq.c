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
typedef  int u16 ;
struct tcpci {int /*<<< orphan*/  port; int /*<<< orphan*/  regmap; } ;
struct pd_message {int /*<<< orphan*/  payload; int /*<<< orphan*/  header; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TCPC_ALERT ; 
 int TCPC_ALERT_CC_STATUS ; 
 int TCPC_ALERT_POWER_STATUS ; 
 int TCPC_ALERT_RX_HARD_RST ; 
 int TCPC_ALERT_RX_STATUS ; 
 int TCPC_ALERT_TX_DISCARDED ; 
 int TCPC_ALERT_TX_FAILED ; 
 int TCPC_ALERT_TX_SUCCESS ; 
 int /*<<< orphan*/  TCPC_POWER_STATUS_MASK ; 
 int /*<<< orphan*/  TCPC_RX_BYTE_CNT ; 
 int /*<<< orphan*/  TCPC_RX_DATA ; 
 int /*<<< orphan*/  TCPC_RX_HDR ; 
 int /*<<< orphan*/  TCPC_TX_DISCARDED ; 
 int /*<<< orphan*/  TCPC_TX_FAILED ; 
 int /*<<< orphan*/  TCPC_TX_SUCCESS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  regmap_raw_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  tcpci_read16 (struct tcpci*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tcpci_write16 (struct tcpci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcpm_cc_change (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_pd_hard_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_pd_receive (int /*<<< orphan*/ ,struct pd_message*) ; 
 int /*<<< orphan*/  tcpm_pd_transmit_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_tcpc_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_vbus_change (int /*<<< orphan*/ ) ; 

irqreturn_t tcpci_irq(struct tcpci *tcpci)
{
	u16 status;

	tcpci_read16(tcpci, TCPC_ALERT, &status);

	/*
	 * Clear alert status for everything except RX_STATUS, which shouldn't
	 * be cleared until we have successfully retrieved message.
	 */
	if (status & ~TCPC_ALERT_RX_STATUS)
		tcpci_write16(tcpci, TCPC_ALERT,
			      status & ~TCPC_ALERT_RX_STATUS);

	if (status & TCPC_ALERT_CC_STATUS)
		tcpm_cc_change(tcpci->port);

	if (status & TCPC_ALERT_POWER_STATUS) {
		unsigned int reg;

		regmap_read(tcpci->regmap, TCPC_POWER_STATUS_MASK, &reg);

		/*
		 * If power status mask has been reset, then the TCPC
		 * has reset.
		 */
		if (reg == 0xff)
			tcpm_tcpc_reset(tcpci->port);
		else
			tcpm_vbus_change(tcpci->port);
	}

	if (status & TCPC_ALERT_RX_STATUS) {
		struct pd_message msg;
		unsigned int cnt;
		u16 header;

		regmap_read(tcpci->regmap, TCPC_RX_BYTE_CNT, &cnt);

		tcpci_read16(tcpci, TCPC_RX_HDR, &header);
		msg.header = cpu_to_le16(header);

		if (WARN_ON(cnt > sizeof(msg.payload)))
			cnt = sizeof(msg.payload);

		if (cnt > 0)
			regmap_raw_read(tcpci->regmap, TCPC_RX_DATA,
					&msg.payload, cnt);

		/* Read complete, clear RX status alert bit */
		tcpci_write16(tcpci, TCPC_ALERT, TCPC_ALERT_RX_STATUS);

		tcpm_pd_receive(tcpci->port, &msg);
	}

	if (status & TCPC_ALERT_RX_HARD_RST)
		tcpm_pd_hard_reset(tcpci->port);

	if (status & TCPC_ALERT_TX_SUCCESS)
		tcpm_pd_transmit_complete(tcpci->port, TCPC_TX_SUCCESS);
	else if (status & TCPC_ALERT_TX_DISCARDED)
		tcpm_pd_transmit_complete(tcpci->port, TCPC_TX_DISCARDED);
	else if (status & TCPC_ALERT_TX_FAILED)
		tcpm_pd_transmit_complete(tcpci->port, TCPC_TX_FAILED);

	return IRQ_HANDLED;
}