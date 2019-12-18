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
 int LEDCFG0_DPDT_SELECT ; 
 int PAD_CTRL1_SW_DPDT_SEL_DATA ; 
 int PWR_DATA_EEPRPAD_RFE_CTRL_EN ; 
 int REG_BT_CONTROL_8723BU ; 
 int /*<<< orphan*/  REG_CR ; 
 int /*<<< orphan*/  REG_LEDCFG0 ; 
 int REG_PAD_CTRL1 ; 
 int /*<<< orphan*/  REG_PWR_DATA ; 
 int /*<<< orphan*/  REG_S0S1_PATH_SWITCH ; 
 int /*<<< orphan*/  REG_SYS_FUNC ; 
 int REG_WLAN_ACT_CONTROL_8723B ; 
 int SYS_FUNC_BBRSTB ; 
 int SYS_FUNC_BB_GLB_RSTN ; 
 int rtl8723b_emu_to_active (struct rtl8xxxu_priv*) ; 
 int /*<<< orphan*/  rtl8xxxu_disabled_to_emu (struct rtl8xxxu_priv*) ; 
 int rtl8xxxu_read16 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int rtl8xxxu_read32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int rtl8xxxu_read8 (struct rtl8xxxu_priv*,int) ; 
 int /*<<< orphan*/  rtl8xxxu_write16 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8xxxu_write32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8xxxu_write8 (struct rtl8xxxu_priv*,int,int) ; 

__attribute__((used)) static int rtl8723bu_power_on(struct rtl8xxxu_priv *priv)
{
	u8 val8;
	u16 val16;
	u32 val32;
	int ret;

	rtl8xxxu_disabled_to_emu(priv);

	ret = rtl8723b_emu_to_active(priv);
	if (ret)
		goto exit;

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

	/*
	 * BT coexist power on settings. This is identical for 1 and 2
	 * antenna parts.
	 */
	rtl8xxxu_write8(priv, REG_PAD_CTRL1 + 3, 0x20);

	val16 = rtl8xxxu_read16(priv, REG_SYS_FUNC);
	val16 |= SYS_FUNC_BBRSTB | SYS_FUNC_BB_GLB_RSTN;
	rtl8xxxu_write16(priv, REG_SYS_FUNC, val16);

	rtl8xxxu_write8(priv, REG_BT_CONTROL_8723BU + 1, 0x18);
	rtl8xxxu_write8(priv, REG_WLAN_ACT_CONTROL_8723B, 0x04);
	rtl8xxxu_write32(priv, REG_S0S1_PATH_SWITCH, 0x00);
	/* Antenna inverse */
	rtl8xxxu_write8(priv, 0xfe08, 0x01);

	val16 = rtl8xxxu_read16(priv, REG_PWR_DATA);
	val16 |= PWR_DATA_EEPRPAD_RFE_CTRL_EN;
	rtl8xxxu_write16(priv, REG_PWR_DATA, val16);

	val32 = rtl8xxxu_read32(priv, REG_LEDCFG0);
	val32 |= LEDCFG0_DPDT_SELECT;
	rtl8xxxu_write32(priv, REG_LEDCFG0, val32);

	val8 = rtl8xxxu_read8(priv, REG_PAD_CTRL1);
	val8 &= ~PAD_CTRL1_SW_DPDT_SEL_DATA;
	rtl8xxxu_write8(priv, REG_PAD_CTRL1, val8);
exit:
	return ret;
}