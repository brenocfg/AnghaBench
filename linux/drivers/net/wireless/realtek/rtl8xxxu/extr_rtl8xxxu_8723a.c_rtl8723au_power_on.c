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
typedef  int u32 ;
typedef  int u16 ;
struct rtl8xxxu_priv {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int CR_CALTIMER_ENABLE ; 
 int CR_HCI_RXDMA_ENABLE ; 
 int CR_HCI_TXDMA_ENABLE ; 
 int CR_MAC_RX_ENABLE ; 
 int CR_MAC_TX_ENABLE ; 
 int CR_PROTOCOL_ENABLE ; 
 int CR_RXDMA_ENABLE ; 
 int CR_SCHEDULE_ENABLE ; 
 int CR_SECURITY_ENABLE ; 
 int CR_TXDMA_ENABLE ; 
 scalar_t__ REG_APS_FSMCO ; 
 int /*<<< orphan*/  REG_CR ; 
 int /*<<< orphan*/  REG_EFUSE_CTRL ; 
 scalar_t__ REG_RSV_CTRL ; 
 int rtl8723a_emu_to_active (struct rtl8xxxu_priv*) ; 
 int /*<<< orphan*/  rtl8xxxu_disabled_to_emu (struct rtl8xxxu_priv*) ; 
 int rtl8xxxu_read16 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int rtl8xxxu_read32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int rtl8xxxu_read8 (struct rtl8xxxu_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl8xxxu_write16 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8xxxu_write32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8xxxu_write8 (struct rtl8xxxu_priv*,scalar_t__,int) ; 

__attribute__((used)) static int rtl8723au_power_on(struct rtl8xxxu_priv *priv)
{
	u8 val8;
	u16 val16;
	u32 val32;
	int ret;

	/*
	 * RSV_CTRL 0x001C[7:0] = 0x00, unlock ISO/CLK/Power control register
	 */
	rtl8xxxu_write8(priv, REG_RSV_CTRL, 0x0);

	rtl8xxxu_disabled_to_emu(priv);

	ret = rtl8723a_emu_to_active(priv);
	if (ret)
		goto exit;

	/*
	 * 0x0004[19] = 1, reset 8051
	 */
	val8 = rtl8xxxu_read8(priv, REG_APS_FSMCO + 2);
	val8 |= BIT(3);
	rtl8xxxu_write8(priv, REG_APS_FSMCO + 2, val8);

	/*
	 * Enable MAC DMA/WMAC/SCHEDULE/SEC block
	 * Set CR bit10 to enable 32k calibration.
	 */
	val16 = rtl8xxxu_read16(priv, REG_CR);
	val16 |= (CR_HCI_TXDMA_ENABLE | CR_HCI_RXDMA_ENABLE |
		  CR_TXDMA_ENABLE | CR_RXDMA_ENABLE |
		  CR_PROTOCOL_ENABLE | CR_SCHEDULE_ENABLE |
		  CR_MAC_TX_ENABLE | CR_MAC_RX_ENABLE |
		  CR_SECURITY_ENABLE | CR_CALTIMER_ENABLE);
	rtl8xxxu_write16(priv, REG_CR, val16);

	/* For EFuse PG */
	val32 = rtl8xxxu_read32(priv, REG_EFUSE_CTRL);
	val32 &= ~(BIT(28) | BIT(29) | BIT(30));
	val32 |= (0x06 << 28);
	rtl8xxxu_write32(priv, REG_EFUSE_CTRL, val32);
exit:
	return ret;
}