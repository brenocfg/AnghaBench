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
typedef  int u32 ;
struct r8152 {int version; TYPE_1__* netdev; } ;
struct TYPE_2__ {int mtu; } ;

/* Variables and functions */
 int ALDPS_PROXY_MODE ; 
 int DIS_MCU_CLROOB ; 
 int ETH_FCS_LEN ; 
 int LINK_LIST_READY ; 
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int NOW_IS_OOB ; 
 int /*<<< orphan*/  PLA_BDC_CR ; 
 int /*<<< orphan*/  PLA_OOB_CTRL ; 
 int /*<<< orphan*/  PLA_RCR ; 
 int /*<<< orphan*/  PLA_RMS ; 
 int /*<<< orphan*/  PLA_SFF_STS_7 ; 
 int /*<<< orphan*/  PLA_TEREDO_CFG ; 
 int /*<<< orphan*/  PLA_TEREDO_WAKE_BASE ; 
 int RCR_AB ; 
 int RCR_AM ; 
 int RCR_APM ; 
 int RE_INIT_LL ; 
#define  RTL_VER_03 133 
#define  RTL_VER_04 132 
#define  RTL_VER_05 131 
#define  RTL_VER_06 130 
#define  RTL_VER_08 129 
#define  RTL_VER_09 128 
 int TEREDO_WAKE_MASK ; 
 int VLAN_ETH_HLEN ; 
 int ocp_read_byte (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocp_read_dword (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocp_read_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_write_byte (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocp_write_dword (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocp_write_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r8153_mac_clk_spd (struct r8152*,int) ; 
 int /*<<< orphan*/  rtl_disable (struct r8152*) ; 
 int /*<<< orphan*/  rtl_reset_bmu (struct r8152*) ; 
 int /*<<< orphan*/  rtl_rx_vlan_en (struct r8152*,int) ; 
 int /*<<< orphan*/  rxdy_gated_en (struct r8152*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void r8153_enter_oob(struct r8152 *tp)
{
	u32 ocp_data;
	int i;

	r8153_mac_clk_spd(tp, true);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data &= ~NOW_IS_OOB;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	rtl_disable(tp);
	rtl_reset_bmu(tp);

	for (i = 0; i < 1000; i++) {
		ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
		if (ocp_data & LINK_LIST_READY)
			break;
		usleep_range(1000, 2000);
	}

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data |= RE_INIT_LL;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	for (i = 0; i < 1000; i++) {
		ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
		if (ocp_data & LINK_LIST_READY)
			break;
		usleep_range(1000, 2000);
	}

	ocp_data = tp->netdev->mtu + VLAN_ETH_HLEN + ETH_FCS_LEN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RMS, ocp_data);

	switch (tp->version) {
	case RTL_VER_03:
	case RTL_VER_04:
	case RTL_VER_05:
	case RTL_VER_06:
		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_TEREDO_CFG);
		ocp_data &= ~TEREDO_WAKE_MASK;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_TEREDO_CFG, ocp_data);
		break;

	case RTL_VER_08:
	case RTL_VER_09:
		/* Clear teredo wake event. bit[15:8] is the teredo wakeup
		 * type. Set it to zero. bits[7:0] are the W1C bits about
		 * the events. Set them to all 1 to clear them.
		 */
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_TEREDO_WAKE_BASE, 0x00ff);
		break;

	default:
		break;
	}

	rtl_rx_vlan_en(tp, true);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_BDC_CR);
	ocp_data |= ALDPS_PROXY_MODE;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_BDC_CR, ocp_data);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data |= NOW_IS_OOB | DIS_MCU_CLROOB;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	rxdy_gated_en(tp, false);

	ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data |= RCR_APM | RCR_AM | RCR_AB;
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);
}