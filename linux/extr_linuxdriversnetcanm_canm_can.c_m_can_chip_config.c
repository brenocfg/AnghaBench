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
struct net_device {int dummy; } ;
struct TYPE_4__ {int ctrlmode; } ;
struct m_can_priv {int version; TYPE_2__ can; TYPE_1__* mcfg; } ;
struct TYPE_3__ {int off; int num; } ;

/* Variables and functions */
 int CAN_CTRLMODE_BERR_REPORTING ; 
 int CAN_CTRLMODE_FD ; 
 int CAN_CTRLMODE_FD_NON_ISO ; 
 int CAN_CTRLMODE_LISTENONLY ; 
 int CAN_CTRLMODE_LOOPBACK ; 
 int CCCR_BRSE ; 
 int CCCR_CME_CANFD_BRS ; 
 int CCCR_CME_MASK ; 
 int CCCR_CME_SHIFT ; 
 int CCCR_CMR_MASK ; 
 int CCCR_CMR_SHIFT ; 
 int CCCR_FDOE ; 
 int CCCR_MON ; 
 int CCCR_NISO ; 
 int CCCR_TEST ; 
 int ILS_ALL_INT0 ; 
 int IR_ALL_INT ; 
 int IR_ERR_LEC_30X ; 
 int IR_ERR_LEC_31X ; 
 size_t MRAM_RXF0 ; 
 size_t MRAM_RXF1 ; 
 size_t MRAM_TXB ; 
 size_t MRAM_TXE ; 
 int /*<<< orphan*/  M_CAN_CCCR ; 
 int /*<<< orphan*/  M_CAN_GFC ; 
 int /*<<< orphan*/  M_CAN_IE ; 
 int /*<<< orphan*/  M_CAN_ILS ; 
 int /*<<< orphan*/  M_CAN_IR ; 
 int /*<<< orphan*/  M_CAN_RXESC ; 
 int M_CAN_RXESC_64BYTES ; 
 int /*<<< orphan*/  M_CAN_RXF0C ; 
 int /*<<< orphan*/  M_CAN_RXF1C ; 
 int /*<<< orphan*/  M_CAN_TEST ; 
 int /*<<< orphan*/  M_CAN_TXBC ; 
 int /*<<< orphan*/  M_CAN_TXEFC ; 
 int /*<<< orphan*/  M_CAN_TXESC ; 
 int RXFC_FS_SHIFT ; 
 int TEST_LBCK ; 
 int TXBC_NDTB_SHIFT ; 
 int TXBC_TFQS_SHIFT ; 
 int TXEFC_EFS_MASK ; 
 int TXEFC_EFS_SHIFT ; 
 int TXESC_TBDS_64BYTES ; 
 int /*<<< orphan*/  m_can_config_endisable (struct m_can_priv*,int) ; 
 int m_can_read (struct m_can_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_can_set_bittiming (struct net_device*) ; 
 int /*<<< orphan*/  m_can_write (struct m_can_priv*,int /*<<< orphan*/ ,int) ; 
 struct m_can_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void m_can_chip_config(struct net_device *dev)
{
	struct m_can_priv *priv = netdev_priv(dev);
	u32 cccr, test;

	m_can_config_endisable(priv, true);

	/* RX Buffer/FIFO Element Size 64 bytes data field */
	m_can_write(priv, M_CAN_RXESC, M_CAN_RXESC_64BYTES);

	/* Accept Non-matching Frames Into FIFO 0 */
	m_can_write(priv, M_CAN_GFC, 0x0);

	if (priv->version == 30) {
		/* only support one Tx Buffer currently */
		m_can_write(priv, M_CAN_TXBC, (1 << TXBC_NDTB_SHIFT) |
				priv->mcfg[MRAM_TXB].off);
	} else {
		/* TX FIFO is used for newer IP Core versions */
		m_can_write(priv, M_CAN_TXBC,
			    (priv->mcfg[MRAM_TXB].num << TXBC_TFQS_SHIFT) |
			    (priv->mcfg[MRAM_TXB].off));
	}

	/* support 64 bytes payload */
	m_can_write(priv, M_CAN_TXESC, TXESC_TBDS_64BYTES);

	/* TX Event FIFO */
	if (priv->version == 30) {
		m_can_write(priv, M_CAN_TXEFC, (1 << TXEFC_EFS_SHIFT) |
				priv->mcfg[MRAM_TXE].off);
	} else {
		/* Full TX Event FIFO is used */
		m_can_write(priv, M_CAN_TXEFC,
			    ((priv->mcfg[MRAM_TXE].num << TXEFC_EFS_SHIFT)
			     & TXEFC_EFS_MASK) |
			    priv->mcfg[MRAM_TXE].off);
	}

	/* rx fifo configuration, blocking mode, fifo size 1 */
	m_can_write(priv, M_CAN_RXF0C,
		    (priv->mcfg[MRAM_RXF0].num << RXFC_FS_SHIFT) |
		     priv->mcfg[MRAM_RXF0].off);

	m_can_write(priv, M_CAN_RXF1C,
		    (priv->mcfg[MRAM_RXF1].num << RXFC_FS_SHIFT) |
		     priv->mcfg[MRAM_RXF1].off);

	cccr = m_can_read(priv, M_CAN_CCCR);
	test = m_can_read(priv, M_CAN_TEST);
	test &= ~TEST_LBCK;
	if (priv->version == 30) {
	/* Version 3.0.x */

		cccr &= ~(CCCR_TEST | CCCR_MON |
			(CCCR_CMR_MASK << CCCR_CMR_SHIFT) |
			(CCCR_CME_MASK << CCCR_CME_SHIFT));

		if (priv->can.ctrlmode & CAN_CTRLMODE_FD)
			cccr |= CCCR_CME_CANFD_BRS << CCCR_CME_SHIFT;

	} else {
	/* Version 3.1.x or 3.2.x */
		cccr &= ~(CCCR_TEST | CCCR_MON | CCCR_BRSE | CCCR_FDOE |
			  CCCR_NISO);

		/* Only 3.2.x has NISO Bit implemented */
		if (priv->can.ctrlmode & CAN_CTRLMODE_FD_NON_ISO)
			cccr |= CCCR_NISO;

		if (priv->can.ctrlmode & CAN_CTRLMODE_FD)
			cccr |= (CCCR_BRSE | CCCR_FDOE);
	}

	/* Loopback Mode */
	if (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK) {
		cccr |= CCCR_TEST | CCCR_MON;
		test |= TEST_LBCK;
	}

	/* Enable Monitoring (all versions) */
	if (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		cccr |= CCCR_MON;

	/* Write config */
	m_can_write(priv, M_CAN_CCCR, cccr);
	m_can_write(priv, M_CAN_TEST, test);

	/* Enable interrupts */
	m_can_write(priv, M_CAN_IR, IR_ALL_INT);
	if (!(priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING))
		if (priv->version == 30)
			m_can_write(priv, M_CAN_IE, IR_ALL_INT &
				    ~(IR_ERR_LEC_30X));
		else
			m_can_write(priv, M_CAN_IE, IR_ALL_INT &
				    ~(IR_ERR_LEC_31X));
	else
		m_can_write(priv, M_CAN_IE, IR_ALL_INT);

	/* route all interrupts to INT0 */
	m_can_write(priv, M_CAN_ILS, ILS_ALL_INT0);

	/* set bittiming params */
	m_can_set_bittiming(dev);

	m_can_config_endisable(priv, false);
}