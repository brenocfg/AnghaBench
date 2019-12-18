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
struct r8152 {int dummy; } ;

/* Variables and functions */
 int ALDPS_PROXY_MODE ; 
 int DIS_MCU_CLROOB ; 
 int LINK_LIST_READY ; 
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int NOW_IS_OOB ; 
 int /*<<< orphan*/  PLA_BDC_CR ; 
 int /*<<< orphan*/  PLA_OOB_CTRL ; 
 int /*<<< orphan*/  PLA_RCR ; 
 int /*<<< orphan*/  PLA_RMS ; 
 int /*<<< orphan*/  PLA_RXFIFO_CTRL0 ; 
 int /*<<< orphan*/  PLA_RXFIFO_CTRL1 ; 
 int /*<<< orphan*/  PLA_RXFIFO_CTRL2 ; 
 int /*<<< orphan*/  PLA_SFF_STS_7 ; 
 int RCR_AB ; 
 int RCR_AM ; 
 int RCR_APM ; 
 int RE_INIT_LL ; 
 int RTL8152_RMS ; 
 int RXFIFO_THR1_OOB ; 
 int RXFIFO_THR2_OOB ; 
 int RXFIFO_THR3_OOB ; 
 int ocp_read_byte (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocp_read_dword (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocp_read_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_write_byte (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocp_write_dword (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocp_write_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_disable (struct r8152*) ; 
 int /*<<< orphan*/  rtl_rx_vlan_en (struct r8152*,int) ; 
 int /*<<< orphan*/  rxdy_gated_en (struct r8152*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void r8152b_enter_oob(struct r8152 *tp)
{
	u32 ocp_data;
	int i;

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data &= ~NOW_IS_OOB;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL0, RXFIFO_THR1_OOB);
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL1, RXFIFO_THR2_OOB);
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL2, RXFIFO_THR3_OOB);

	rtl_disable(tp);

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

	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RMS, RTL8152_RMS);

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