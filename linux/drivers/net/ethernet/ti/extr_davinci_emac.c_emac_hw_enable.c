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
struct emac_priv {int speed; scalar_t__ duplex; int rx_addr_type; int /*<<< orphan*/  napi; int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int EMAC_DEF_BCAST_CH ; 
 scalar_t__ EMAC_DEF_BCAST_EN ; 
 int EMAC_DEF_BUFFER_OFFSET ; 
 scalar_t__ EMAC_DEF_ERROR_FRAME_EN ; 
 scalar_t__ EMAC_DEF_MACCTRL_FRAME_EN ; 
 int EMAC_DEF_MAX_FRAME_SIZE ; 
 int EMAC_DEF_MCAST_CH ; 
 scalar_t__ EMAC_DEF_MCAST_EN ; 
 scalar_t__ EMAC_DEF_NO_BUFF_CHAIN ; 
 scalar_t__ EMAC_DEF_PASS_CRC ; 
 int EMAC_DEF_PROM_CH ; 
 scalar_t__ EMAC_DEF_PROM_EN ; 
 scalar_t__ EMAC_DEF_QOS_EN ; 
 int /*<<< orphan*/  EMAC_DEF_RX_CH ; 
 scalar_t__ EMAC_DEF_SHORT_FRAME_EN ; 
 scalar_t__ EMAC_DEF_TXPACING_EN ; 
 scalar_t__ EMAC_DEF_TXPRIO_FIXED ; 
 int /*<<< orphan*/  EMAC_MACCONFIG ; 
 int /*<<< orphan*/  EMAC_MACCONTROL ; 
 int EMAC_MACCONTROL_GIGABITEN ; 
 int EMAC_MACCONTROL_GMIIEN ; 
 int EMAC_MACCONTROL_TXPACEEN ; 
 int EMAC_MACCONTROL_TXPTYPE ; 
 int /*<<< orphan*/  EMAC_MACINTMASKSET ; 
 int EMAC_MAC_HOST_ERR_INTMASK_VAL ; 
 int /*<<< orphan*/  EMAC_RXBUFFEROFFSET ; 
 int /*<<< orphan*/  EMAC_RXFILTERLOWTHRESH ; 
 int /*<<< orphan*/  EMAC_RXMAXLEN ; 
 int /*<<< orphan*/  EMAC_RXMBPENABLE ; 
 int EMAC_RXMBP_BROADCH_SHIFT ; 
 int EMAC_RXMBP_BROADEN_MASK ; 
 int EMAC_RXMBP_CAFEN_MASK ; 
 int EMAC_RXMBP_CEFEN_MASK ; 
 int EMAC_RXMBP_CHMASK ; 
 int EMAC_RXMBP_CMFEN_MASK ; 
 int EMAC_RXMBP_CSFEN_MASK ; 
 int EMAC_RXMBP_MULTICH_SHIFT ; 
 int EMAC_RXMBP_MULTIEN_MASK ; 
 int EMAC_RXMBP_NOCHAIN_MASK ; 
 int EMAC_RXMBP_PASSCRC_MASK ; 
 int EMAC_RXMBP_PROMCH_SHIFT ; 
 int EMAC_RXMBP_QOSEN_MASK ; 
 int /*<<< orphan*/  EMAC_RXUNICASTCLEAR ; 
 int EMAC_RX_BUFFER_OFFSET_MASK ; 
 int EMAC_RX_MAX_LEN_MASK ; 
 int EMAC_RX_UNICAST_CLEAR_ALL ; 
 int /*<<< orphan*/  EMAC_SOFTRESET ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  emac_int_disable (struct emac_priv*) ; 
 int /*<<< orphan*/  emac_int_enable (struct emac_priv*) ; 
 int emac_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_setmac (struct emac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int emac_hw_enable(struct emac_priv *priv)
{
	u32 val, mbp_enable, mac_control;

	/* Soft reset */
	emac_write(EMAC_SOFTRESET, 1);
	while (emac_read(EMAC_SOFTRESET))
		cpu_relax();

	/* Disable interrupt & Set pacing for more interrupts initially */
	emac_int_disable(priv);

	/* Full duplex enable bit set when auto negotiation happens */
	mac_control =
		(((EMAC_DEF_TXPRIO_FIXED) ? (EMAC_MACCONTROL_TXPTYPE) : 0x0) |
		((priv->speed == 1000) ? EMAC_MACCONTROL_GIGABITEN : 0x0) |
		((EMAC_DEF_TXPACING_EN) ? (EMAC_MACCONTROL_TXPACEEN) : 0x0) |
		((priv->duplex == DUPLEX_FULL) ? 0x1 : 0));
	emac_write(EMAC_MACCONTROL, mac_control);

	mbp_enable =
		(((EMAC_DEF_PASS_CRC) ? (EMAC_RXMBP_PASSCRC_MASK) : 0x0) |
		((EMAC_DEF_QOS_EN) ? (EMAC_RXMBP_QOSEN_MASK) : 0x0) |
		 ((EMAC_DEF_NO_BUFF_CHAIN) ? (EMAC_RXMBP_NOCHAIN_MASK) : 0x0) |
		 ((EMAC_DEF_MACCTRL_FRAME_EN) ? (EMAC_RXMBP_CMFEN_MASK) : 0x0) |
		 ((EMAC_DEF_SHORT_FRAME_EN) ? (EMAC_RXMBP_CSFEN_MASK) : 0x0) |
		 ((EMAC_DEF_ERROR_FRAME_EN) ? (EMAC_RXMBP_CEFEN_MASK) : 0x0) |
		 ((EMAC_DEF_PROM_EN) ? (EMAC_RXMBP_CAFEN_MASK) : 0x0) |
		 ((EMAC_DEF_PROM_CH & EMAC_RXMBP_CHMASK) << \
			EMAC_RXMBP_PROMCH_SHIFT) |
		 ((EMAC_DEF_BCAST_EN) ? (EMAC_RXMBP_BROADEN_MASK) : 0x0) |
		 ((EMAC_DEF_BCAST_CH & EMAC_RXMBP_CHMASK) << \
			EMAC_RXMBP_BROADCH_SHIFT) |
		 ((EMAC_DEF_MCAST_EN) ? (EMAC_RXMBP_MULTIEN_MASK) : 0x0) |
		 ((EMAC_DEF_MCAST_CH & EMAC_RXMBP_CHMASK) << \
			EMAC_RXMBP_MULTICH_SHIFT));
	emac_write(EMAC_RXMBPENABLE, mbp_enable);
	emac_write(EMAC_RXMAXLEN, (EMAC_DEF_MAX_FRAME_SIZE &
				   EMAC_RX_MAX_LEN_MASK));
	emac_write(EMAC_RXBUFFEROFFSET, (EMAC_DEF_BUFFER_OFFSET &
					 EMAC_RX_BUFFER_OFFSET_MASK));
	emac_write(EMAC_RXFILTERLOWTHRESH, 0);
	emac_write(EMAC_RXUNICASTCLEAR, EMAC_RX_UNICAST_CLEAR_ALL);
	priv->rx_addr_type = (emac_read(EMAC_MACCONFIG) >> 8) & 0xFF;

	emac_write(EMAC_MACINTMASKSET, EMAC_MAC_HOST_ERR_INTMASK_VAL);

	emac_setmac(priv, EMAC_DEF_RX_CH, priv->mac_addr);

	/* Enable MII */
	val = emac_read(EMAC_MACCONTROL);
	val |= (EMAC_MACCONTROL_GMIIEN);
	emac_write(EMAC_MACCONTROL, val);

	/* Enable NAPI and interrupts */
	napi_enable(&priv->napi);
	emac_int_enable(priv);
	return 0;

}