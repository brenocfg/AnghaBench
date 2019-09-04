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
struct mac_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAMC_RX_MAX_FRAME ; 
 int /*<<< orphan*/  GMAC_AN_NEG_STATE_REG ; 
 int /*<<< orphan*/  GMAC_CF_CRC_STRIP_REG ; 
 int /*<<< orphan*/  GMAC_DUPLEX_TYPE_REG ; 
 int /*<<< orphan*/  GMAC_FC_TX_TIMER_REG ; 
 int /*<<< orphan*/  GMAC_FD_FC_ADDR_HIGH_REG ; 
 int /*<<< orphan*/  GMAC_FD_FC_ADDR_LOW_REG ; 
 int /*<<< orphan*/  GMAC_FD_FC_TYPE_REG ; 
 int /*<<< orphan*/  GMAC_IPG_TX_TIMER_REG ; 
 int /*<<< orphan*/  GMAC_LD_LINK_COUNTER_REG ; 
 int /*<<< orphan*/  GMAC_LINE_LOOP_BACK_REG ; 
 int /*<<< orphan*/  GMAC_LOOP_REG ; 
 int /*<<< orphan*/  GMAC_MAC_SKIP_LEN_REG ; 
 int /*<<< orphan*/  GMAC_MAX_FRM_SIZE_REG ; 
 int /*<<< orphan*/  GMAC_MODE_CHANGE_EN_REG ; 
 int /*<<< orphan*/  GMAC_OCTETS_TRANSMITTED_BAD_REG ; 
 int /*<<< orphan*/  GMAC_OCTETS_TRANSMITTED_OK_REG ; 
 int /*<<< orphan*/  GMAC_PAUSE_EN_REG ; 
 int /*<<< orphan*/  GMAC_PAUSE_THR_REG ; 
 int /*<<< orphan*/  GMAC_PORT_EN_REG ; 
 int /*<<< orphan*/  GMAC_PORT_MODE_REG ; 
 int /*<<< orphan*/  GMAC_PTP_CONFIG_REG ; 
 int /*<<< orphan*/  GMAC_RECV_CONTROL_REG ; 
 int /*<<< orphan*/  GMAC_REC_FILT_CONTROL_REG ; 
 int /*<<< orphan*/  GMAC_RX_ALIGN_ERRORS_REG ; 
 int /*<<< orphan*/  GMAC_RX_BC_PKTS_REG ; 
 int /*<<< orphan*/  GMAC_RX_DATA_ERR_REG ; 
 int /*<<< orphan*/  GMAC_RX_FAIL_COMMA_CNT_REG ; 
 int /*<<< orphan*/  GMAC_RX_FCS_ERRORS_REG ; 
 int /*<<< orphan*/  GMAC_RX_FILT_PKT_CNT_REG ; 
 int /*<<< orphan*/  GMAC_RX_JABBER_ERRORS_REG ; 
 int /*<<< orphan*/  GMAC_RX_LENGTHFIELD_ERR_CNT_REG ; 
 int /*<<< orphan*/  GMAC_RX_LONG_ERRORS_REG ; 
 int /*<<< orphan*/  GMAC_RX_MC_PKTS_REG ; 
 int /*<<< orphan*/  GMAC_RX_OCTETS_BAD_REG ; 
 int /*<<< orphan*/  GMAC_RX_OCTETS_TOTAL_FILT_REG ; 
 int /*<<< orphan*/  GMAC_RX_OCTETS_TOTAL_OK_REG ; 
 int /*<<< orphan*/  GMAC_RX_OVERRUN_CNT_REG ; 
 int /*<<< orphan*/  GMAC_RX_PAUSE_MACCTRL_FRAM_REG ; 
 int /*<<< orphan*/  GMAC_RX_PKTS_1024TO1518OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_RX_PKTS_128TO255OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_RX_PKTS_1519TOMAXOCTETS_REG ; 
 int /*<<< orphan*/  GMAC_RX_PKTS_255TO511OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_RX_PKTS_512TO1023OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_RX_PKTS_64OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_RX_PKTS_65TO127OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_RX_RUNT_ERR_CNT_REG ; 
 int /*<<< orphan*/  GMAC_RX_SHORT_ERR_CNT_REG ; 
 int /*<<< orphan*/  GMAC_RX_TAGGED_REG ; 
 int /*<<< orphan*/  GMAC_RX_UC_PKTS_REG ; 
 int /*<<< orphan*/  GMAC_RX_UNKNOWN_MACCTRL_FRAM_REG ; 
 int /*<<< orphan*/  GMAC_RX_VERY_LONG_ERR_CNT_REG ; 
 int /*<<< orphan*/  GMAC_SHORT_RUNTS_THR_REG ; 
 int /*<<< orphan*/  GMAC_SIXTEEN_BIT_CNTR_REG ; 
 int /*<<< orphan*/  GMAC_STATION_ADDR_HIGH_0_REG ; 
 int /*<<< orphan*/  GMAC_STATION_ADDR_HIGH_1_REG ; 
 int /*<<< orphan*/  GMAC_STATION_ADDR_HIGH_2_REG ; 
 int /*<<< orphan*/  GMAC_STATION_ADDR_HIGH_3_REG ; 
 int /*<<< orphan*/  GMAC_STATION_ADDR_HIGH_4_REG ; 
 int /*<<< orphan*/  GMAC_STATION_ADDR_HIGH_5_REG ; 
 int /*<<< orphan*/  GMAC_STATION_ADDR_HIGH_MSK_0_REG ; 
 int /*<<< orphan*/  GMAC_STATION_ADDR_HIGH_MSK_1_REG ; 
 int /*<<< orphan*/  GMAC_STATION_ADDR_LOW_0_REG ; 
 int /*<<< orphan*/  GMAC_STATION_ADDR_LOW_1_REG ; 
 int /*<<< orphan*/  GMAC_STATION_ADDR_LOW_2_REG ; 
 int /*<<< orphan*/  GMAC_STATION_ADDR_LOW_3_REG ; 
 int /*<<< orphan*/  GMAC_STATION_ADDR_LOW_4_REG ; 
 int /*<<< orphan*/  GMAC_STATION_ADDR_LOW_5_REG ; 
 int /*<<< orphan*/  GMAC_STATION_ADDR_LOW_MSK_0_REG ; 
 int /*<<< orphan*/  GMAC_STATION_ADDR_LOW_MSK_1_REG ; 
 int /*<<< orphan*/  GMAC_TRANSMIT_CONTROL_REG ; 
 int /*<<< orphan*/  GMAC_TX_BC_PKTS_REG ; 
 int /*<<< orphan*/  GMAC_TX_CRC_ERROR_REG ; 
 int /*<<< orphan*/  GMAC_TX_EXCESSIVE_LENGTH_DROP_REG ; 
 int /*<<< orphan*/  GMAC_TX_LOCAL_PAGE_REG ; 
 int /*<<< orphan*/  GMAC_TX_LOOP_PKT_PRI_REG ; 
 int /*<<< orphan*/  GMAC_TX_MC_PKTS_REG ; 
 int /*<<< orphan*/  GMAC_TX_PAUSE_FRAMES_REG ; 
 int /*<<< orphan*/  GMAC_TX_PKTS_1024TO1518OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_TX_PKTS_128TO255OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_TX_PKTS_1519TOMAXOCTETS_REG ; 
 int /*<<< orphan*/  GMAC_TX_PKTS_255TO511OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_TX_PKTS_512TO1023OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_TX_PKTS_64OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_TX_PKTS_65TO127OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_TX_TAGGED_REG ; 
 int /*<<< orphan*/  GMAC_TX_UC_PKTS_REG ; 
 int /*<<< orphan*/  GMAC_TX_UNDERRUN_REG ; 
 int /*<<< orphan*/  GMAC_VLAN_CODE_REG ; 
 int dsaf_read_dev (struct mac_driver*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_gmac_get_regs(void *mac_drv, void *data)
{
	u32 *regs = data;
	int i;
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	/* base config registers */
	regs[0] = dsaf_read_dev(drv, GMAC_DUPLEX_TYPE_REG);
	regs[1] = dsaf_read_dev(drv, GMAC_FD_FC_TYPE_REG);
	regs[2] = dsaf_read_dev(drv, GMAC_FC_TX_TIMER_REG);
	regs[3] = dsaf_read_dev(drv, GMAC_FD_FC_ADDR_LOW_REG);
	regs[4] = dsaf_read_dev(drv, GMAC_FD_FC_ADDR_HIGH_REG);
	regs[5] = dsaf_read_dev(drv, GMAC_IPG_TX_TIMER_REG);
	regs[6] = dsaf_read_dev(drv, GMAC_PAUSE_THR_REG);
	regs[7] = dsaf_read_dev(drv, GMAC_MAX_FRM_SIZE_REG);
	regs[8] = dsaf_read_dev(drv, GMAC_PORT_MODE_REG);
	regs[9] = dsaf_read_dev(drv, GMAC_PORT_EN_REG);
	regs[10] = dsaf_read_dev(drv, GMAC_PAUSE_EN_REG);
	regs[11] = dsaf_read_dev(drv, GMAC_SHORT_RUNTS_THR_REG);
	regs[12] = dsaf_read_dev(drv, GMAC_AN_NEG_STATE_REG);
	regs[13] = dsaf_read_dev(drv, GMAC_TX_LOCAL_PAGE_REG);
	regs[14] = dsaf_read_dev(drv, GMAC_TRANSMIT_CONTROL_REG);
	regs[15] = dsaf_read_dev(drv, GMAC_REC_FILT_CONTROL_REG);
	regs[16] = dsaf_read_dev(drv, GMAC_PTP_CONFIG_REG);

	/* rx static registers */
	regs[17] = dsaf_read_dev(drv, GMAC_RX_OCTETS_TOTAL_OK_REG);
	regs[18] = dsaf_read_dev(drv, GMAC_RX_OCTETS_BAD_REG);
	regs[19] = dsaf_read_dev(drv, GMAC_RX_UC_PKTS_REG);
	regs[20] = dsaf_read_dev(drv, GMAC_RX_MC_PKTS_REG);
	regs[21] = dsaf_read_dev(drv, GMAC_RX_BC_PKTS_REG);
	regs[22] = dsaf_read_dev(drv, GMAC_RX_PKTS_64OCTETS_REG);
	regs[23] = dsaf_read_dev(drv, GMAC_RX_PKTS_65TO127OCTETS_REG);
	regs[24] = dsaf_read_dev(drv, GMAC_RX_PKTS_128TO255OCTETS_REG);
	regs[25] = dsaf_read_dev(drv, GMAC_RX_PKTS_255TO511OCTETS_REG);
	regs[26] = dsaf_read_dev(drv, GMAC_RX_PKTS_512TO1023OCTETS_REG);
	regs[27] = dsaf_read_dev(drv, GMAC_RX_PKTS_1024TO1518OCTETS_REG);
	regs[28] = dsaf_read_dev(drv, GMAC_RX_PKTS_1519TOMAXOCTETS_REG);
	regs[29] = dsaf_read_dev(drv, GMAC_RX_FCS_ERRORS_REG);
	regs[30] = dsaf_read_dev(drv, GMAC_RX_TAGGED_REG);
	regs[31] = dsaf_read_dev(drv, GMAC_RX_DATA_ERR_REG);
	regs[32] = dsaf_read_dev(drv, GMAC_RX_ALIGN_ERRORS_REG);
	regs[33] = dsaf_read_dev(drv, GMAC_RX_LONG_ERRORS_REG);
	regs[34] = dsaf_read_dev(drv, GMAC_RX_JABBER_ERRORS_REG);
	regs[35] = dsaf_read_dev(drv, GMAC_RX_PAUSE_MACCTRL_FRAM_REG);
	regs[36] = dsaf_read_dev(drv, GMAC_RX_UNKNOWN_MACCTRL_FRAM_REG);
	regs[37] = dsaf_read_dev(drv, GMAC_RX_VERY_LONG_ERR_CNT_REG);
	regs[38] = dsaf_read_dev(drv, GMAC_RX_RUNT_ERR_CNT_REG);
	regs[39] = dsaf_read_dev(drv, GMAC_RX_SHORT_ERR_CNT_REG);
	regs[40] = dsaf_read_dev(drv, GMAC_RX_FILT_PKT_CNT_REG);
	regs[41] = dsaf_read_dev(drv, GMAC_RX_OCTETS_TOTAL_FILT_REG);

	/* tx static registers */
	regs[42] = dsaf_read_dev(drv, GMAC_OCTETS_TRANSMITTED_OK_REG);
	regs[43] = dsaf_read_dev(drv, GMAC_OCTETS_TRANSMITTED_BAD_REG);
	regs[44] = dsaf_read_dev(drv, GMAC_TX_UC_PKTS_REG);
	regs[45] = dsaf_read_dev(drv, GMAC_TX_MC_PKTS_REG);
	regs[46] = dsaf_read_dev(drv, GMAC_TX_BC_PKTS_REG);
	regs[47] = dsaf_read_dev(drv, GMAC_TX_PKTS_64OCTETS_REG);
	regs[48] = dsaf_read_dev(drv, GMAC_TX_PKTS_65TO127OCTETS_REG);
	regs[49] = dsaf_read_dev(drv, GMAC_TX_PKTS_128TO255OCTETS_REG);
	regs[50] = dsaf_read_dev(drv, GMAC_TX_PKTS_255TO511OCTETS_REG);
	regs[51] = dsaf_read_dev(drv, GMAC_TX_PKTS_512TO1023OCTETS_REG);
	regs[52] = dsaf_read_dev(drv, GMAC_TX_PKTS_1024TO1518OCTETS_REG);
	regs[53] = dsaf_read_dev(drv, GMAC_TX_PKTS_1519TOMAXOCTETS_REG);
	regs[54] = dsaf_read_dev(drv, GMAC_TX_EXCESSIVE_LENGTH_DROP_REG);
	regs[55] = dsaf_read_dev(drv, GMAC_TX_UNDERRUN_REG);
	regs[56] = dsaf_read_dev(drv, GMAC_TX_TAGGED_REG);
	regs[57] = dsaf_read_dev(drv, GMAC_TX_CRC_ERROR_REG);
	regs[58] = dsaf_read_dev(drv, GMAC_TX_PAUSE_FRAMES_REG);

	regs[59] = dsaf_read_dev(drv, GAMC_RX_MAX_FRAME);
	regs[60] = dsaf_read_dev(drv, GMAC_LINE_LOOP_BACK_REG);
	regs[61] = dsaf_read_dev(drv, GMAC_CF_CRC_STRIP_REG);
	regs[62] = dsaf_read_dev(drv, GMAC_MODE_CHANGE_EN_REG);
	regs[63] = dsaf_read_dev(drv, GMAC_SIXTEEN_BIT_CNTR_REG);
	regs[64] = dsaf_read_dev(drv, GMAC_LD_LINK_COUNTER_REG);
	regs[65] = dsaf_read_dev(drv, GMAC_LOOP_REG);
	regs[66] = dsaf_read_dev(drv, GMAC_RECV_CONTROL_REG);
	regs[67] = dsaf_read_dev(drv, GMAC_VLAN_CODE_REG);
	regs[68] = dsaf_read_dev(drv, GMAC_RX_OVERRUN_CNT_REG);
	regs[69] = dsaf_read_dev(drv, GMAC_RX_LENGTHFIELD_ERR_CNT_REG);
	regs[70] = dsaf_read_dev(drv, GMAC_RX_FAIL_COMMA_CNT_REG);

	regs[71] = dsaf_read_dev(drv, GMAC_STATION_ADDR_LOW_0_REG);
	regs[72] = dsaf_read_dev(drv, GMAC_STATION_ADDR_HIGH_0_REG);
	regs[73] = dsaf_read_dev(drv, GMAC_STATION_ADDR_LOW_1_REG);
	regs[74] = dsaf_read_dev(drv, GMAC_STATION_ADDR_HIGH_1_REG);
	regs[75] = dsaf_read_dev(drv, GMAC_STATION_ADDR_LOW_2_REG);
	regs[76] = dsaf_read_dev(drv, GMAC_STATION_ADDR_HIGH_2_REG);
	regs[77] = dsaf_read_dev(drv, GMAC_STATION_ADDR_LOW_3_REG);
	regs[78] = dsaf_read_dev(drv, GMAC_STATION_ADDR_HIGH_3_REG);
	regs[79] = dsaf_read_dev(drv, GMAC_STATION_ADDR_LOW_4_REG);
	regs[80] = dsaf_read_dev(drv, GMAC_STATION_ADDR_HIGH_4_REG);
	regs[81] = dsaf_read_dev(drv, GMAC_STATION_ADDR_LOW_5_REG);
	regs[82] = dsaf_read_dev(drv, GMAC_STATION_ADDR_HIGH_5_REG);
	regs[83] = dsaf_read_dev(drv, GMAC_STATION_ADDR_LOW_MSK_0_REG);
	regs[84] = dsaf_read_dev(drv, GMAC_STATION_ADDR_HIGH_MSK_0_REG);
	regs[85] = dsaf_read_dev(drv, GMAC_STATION_ADDR_LOW_MSK_1_REG);
	regs[86] = dsaf_read_dev(drv, GMAC_STATION_ADDR_HIGH_MSK_1_REG);
	regs[87] = dsaf_read_dev(drv, GMAC_MAC_SKIP_LEN_REG);
	regs[88] = dsaf_read_dev(drv, GMAC_TX_LOOP_PKT_PRI_REG);

	/* mark end of mac regs */
	for (i = 89; i < 96; i++)
		regs[i] = 0xaaaaaaaa;
}