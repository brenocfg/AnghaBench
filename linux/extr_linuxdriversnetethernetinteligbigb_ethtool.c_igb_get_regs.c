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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  b2ogprc; int /*<<< orphan*/  o2bspc; int /*<<< orphan*/  b2ospc; int /*<<< orphan*/  o2bgptc; int /*<<< orphan*/  hrmpc; int /*<<< orphan*/  scvpc; int /*<<< orphan*/  lenerrs; int /*<<< orphan*/  hgotc; int /*<<< orphan*/  hgorc; int /*<<< orphan*/  hgptc; int /*<<< orphan*/  rpthc; int /*<<< orphan*/  iac; int /*<<< orphan*/  tsctc; int /*<<< orphan*/  bptc; int /*<<< orphan*/  mptc; int /*<<< orphan*/  ptc1522; int /*<<< orphan*/  ptc1023; int /*<<< orphan*/  ptc511; int /*<<< orphan*/  ptc255; int /*<<< orphan*/  ptc127; int /*<<< orphan*/  ptc64; int /*<<< orphan*/  tpt; int /*<<< orphan*/  tpr; int /*<<< orphan*/  tot; int /*<<< orphan*/  tor; int /*<<< orphan*/  mgptc; int /*<<< orphan*/  mgpdc; int /*<<< orphan*/  mgprc; int /*<<< orphan*/  rjc; int /*<<< orphan*/  roc; int /*<<< orphan*/  rfc; int /*<<< orphan*/  ruc; int /*<<< orphan*/  rnbc; int /*<<< orphan*/  gotc; int /*<<< orphan*/  gorc; int /*<<< orphan*/  gptc; int /*<<< orphan*/  mprc; int /*<<< orphan*/  bprc; int /*<<< orphan*/  gprc; int /*<<< orphan*/  prc1522; int /*<<< orphan*/  prc1023; int /*<<< orphan*/  prc511; int /*<<< orphan*/  prc255; int /*<<< orphan*/  prc127; int /*<<< orphan*/  prc64; int /*<<< orphan*/  fcruc; int /*<<< orphan*/  xofftxc; int /*<<< orphan*/  xoffrxc; int /*<<< orphan*/  xontxc; int /*<<< orphan*/  xonrxc; int /*<<< orphan*/  rlec; int /*<<< orphan*/  htdpmc; int /*<<< orphan*/  sec; int /*<<< orphan*/  tncrs; int /*<<< orphan*/  dc; int /*<<< orphan*/  colc; int /*<<< orphan*/  latecol; int /*<<< orphan*/  mcc; int /*<<< orphan*/  ecol; int /*<<< orphan*/  scc; int /*<<< orphan*/  mpc; int /*<<< orphan*/  rxerrc; int /*<<< orphan*/  symerrs; int /*<<< orphan*/  algnerrc; int /*<<< orphan*/  crcerrs; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct e1000_hw {int revision_id; unsigned int device_id; TYPE_2__ mac; } ;
struct igb_adapter {TYPE_1__ stats; struct e1000_hw hw; } ;
struct ethtool_regs {unsigned int version; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CONNSW ; 
 int /*<<< orphan*/  E1000_CTRL ; 
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
 int /*<<< orphan*/  E1000_DCA_TXCTRL (int) ; 
 int /*<<< orphan*/  E1000_DTXCTL ; 
 int /*<<< orphan*/  E1000_EECD ; 
 int /*<<< orphan*/  E1000_EIAC ; 
 int /*<<< orphan*/  E1000_EIAM ; 
 int /*<<< orphan*/  E1000_EICS ; 
 int /*<<< orphan*/  E1000_EIMC ; 
 int /*<<< orphan*/  E1000_EIMS ; 
 int /*<<< orphan*/  E1000_EITR (int) ; 
 int /*<<< orphan*/  E1000_FCAH ; 
 int /*<<< orphan*/  E1000_FCAL ; 
 int /*<<< orphan*/  E1000_FCRTH ; 
 int /*<<< orphan*/  E1000_FCRTL ; 
 int /*<<< orphan*/  E1000_FCRTV ; 
 int /*<<< orphan*/  E1000_FCTTV ; 
 int /*<<< orphan*/  E1000_FFLT_REG (int) ; 
 int /*<<< orphan*/  E1000_FFMT_REG (int) ; 
 int /*<<< orphan*/  E1000_FFVT_REG (int) ; 
 int /*<<< orphan*/  E1000_FRTIMER ; 
 int /*<<< orphan*/  E1000_IAC ; 
 int /*<<< orphan*/  E1000_IAM ; 
 int /*<<< orphan*/  E1000_ICS ; 
 int /*<<< orphan*/  E1000_IMC ; 
 int /*<<< orphan*/  E1000_IMIR (int) ; 
 int /*<<< orphan*/  E1000_IMIREXT (int) ; 
 int /*<<< orphan*/  E1000_IMIRVP ; 
 int /*<<< orphan*/  E1000_IMS ; 
 int /*<<< orphan*/  E1000_IP4AT_REG (int) ; 
 int /*<<< orphan*/  E1000_IP6AT_REG (int) ; 
 int /*<<< orphan*/  E1000_IPAV ; 
 int /*<<< orphan*/  E1000_LEDCTL ; 
 int /*<<< orphan*/  E1000_MDIC ; 
 int /*<<< orphan*/  E1000_MRQC ; 
 int /*<<< orphan*/  E1000_PBA ; 
 int /*<<< orphan*/  E1000_PBS ; 
 int /*<<< orphan*/  E1000_PCS_ANADV ; 
 int /*<<< orphan*/  E1000_PCS_CFG0 ; 
 int /*<<< orphan*/  E1000_PCS_LCTL ; 
 int /*<<< orphan*/  E1000_PCS_LPAB ; 
 int /*<<< orphan*/  E1000_PCS_LPABNP ; 
 int /*<<< orphan*/  E1000_PCS_LSTAT ; 
 int /*<<< orphan*/  E1000_PCS_NPTX ; 
 int /*<<< orphan*/  E1000_PSRTYPE (int) ; 
 int /*<<< orphan*/  E1000_RAH (int) ; 
 int /*<<< orphan*/  E1000_RAL (int) ; 
 int /*<<< orphan*/  E1000_RCTL ; 
 int /*<<< orphan*/  E1000_RDBAH (int) ; 
 int /*<<< orphan*/  E1000_RDBAL (int) ; 
 int /*<<< orphan*/  E1000_RDH (int) ; 
 int /*<<< orphan*/  E1000_RDLEN (int) ; 
 int /*<<< orphan*/  E1000_RDT (int) ; 
 int /*<<< orphan*/  E1000_RFCTL ; 
 int /*<<< orphan*/  E1000_RLPML ; 
 int /*<<< orphan*/  E1000_RXCSUM ; 
 int /*<<< orphan*/  E1000_RXDCTL (int) ; 
 int /*<<< orphan*/  E1000_SCTL ; 
 int /*<<< orphan*/  E1000_SRRCTL (int) ; 
 int /*<<< orphan*/  E1000_STATUS ; 
 int /*<<< orphan*/  E1000_TCPTIMER ; 
 int /*<<< orphan*/  E1000_TCTL ; 
 int /*<<< orphan*/  E1000_TCTL_EXT ; 
 int /*<<< orphan*/  E1000_TDBAH (int) ; 
 int /*<<< orphan*/  E1000_TDBAL (int) ; 
 int /*<<< orphan*/  E1000_TDFH ; 
 int /*<<< orphan*/  E1000_TDFHS ; 
 int /*<<< orphan*/  E1000_TDFPC ; 
 int /*<<< orphan*/  E1000_TDFT ; 
 int /*<<< orphan*/  E1000_TDH (int) ; 
 int /*<<< orphan*/  E1000_TDLEN (int) ; 
 int /*<<< orphan*/  E1000_TDT (int) ; 
 int /*<<< orphan*/  E1000_TDWBAH (int) ; 
 int /*<<< orphan*/  E1000_TDWBAL (int) ; 
 int /*<<< orphan*/  E1000_TIPG ; 
 int /*<<< orphan*/  E1000_TXDCTL (int) ; 
 int /*<<< orphan*/  E1000_VET ; 
 int /*<<< orphan*/  E1000_VT_CTL ; 
 int /*<<< orphan*/  E1000_WUC ; 
 int /*<<< orphan*/  E1000_WUFC ; 
 int /*<<< orphan*/  E1000_WUPL ; 
 int /*<<< orphan*/  E1000_WUPM_REG (int) ; 
 int /*<<< orphan*/  E1000_WUS ; 
 int IGB_REGS_LEN ; 
 scalar_t__ e1000_82576 ; 
 scalar_t__ e1000_82580 ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igb_get_regs(struct net_device *netdev,
			 struct ethtool_regs *regs, void *p)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	u32 *regs_buff = p;
	u8 i;

	memset(p, 0, IGB_REGS_LEN * sizeof(u32));

	regs->version = (1u << 24) | (hw->revision_id << 16) | hw->device_id;

	/* General Registers */
	regs_buff[0] = rd32(E1000_CTRL);
	regs_buff[1] = rd32(E1000_STATUS);
	regs_buff[2] = rd32(E1000_CTRL_EXT);
	regs_buff[3] = rd32(E1000_MDIC);
	regs_buff[4] = rd32(E1000_SCTL);
	regs_buff[5] = rd32(E1000_CONNSW);
	regs_buff[6] = rd32(E1000_VET);
	regs_buff[7] = rd32(E1000_LEDCTL);
	regs_buff[8] = rd32(E1000_PBA);
	regs_buff[9] = rd32(E1000_PBS);
	regs_buff[10] = rd32(E1000_FRTIMER);
	regs_buff[11] = rd32(E1000_TCPTIMER);

	/* NVM Register */
	regs_buff[12] = rd32(E1000_EECD);

	/* Interrupt */
	/* Reading EICS for EICR because they read the
	 * same but EICS does not clear on read
	 */
	regs_buff[13] = rd32(E1000_EICS);
	regs_buff[14] = rd32(E1000_EICS);
	regs_buff[15] = rd32(E1000_EIMS);
	regs_buff[16] = rd32(E1000_EIMC);
	regs_buff[17] = rd32(E1000_EIAC);
	regs_buff[18] = rd32(E1000_EIAM);
	/* Reading ICS for ICR because they read the
	 * same but ICS does not clear on read
	 */
	regs_buff[19] = rd32(E1000_ICS);
	regs_buff[20] = rd32(E1000_ICS);
	regs_buff[21] = rd32(E1000_IMS);
	regs_buff[22] = rd32(E1000_IMC);
	regs_buff[23] = rd32(E1000_IAC);
	regs_buff[24] = rd32(E1000_IAM);
	regs_buff[25] = rd32(E1000_IMIRVP);

	/* Flow Control */
	regs_buff[26] = rd32(E1000_FCAL);
	regs_buff[27] = rd32(E1000_FCAH);
	regs_buff[28] = rd32(E1000_FCTTV);
	regs_buff[29] = rd32(E1000_FCRTL);
	regs_buff[30] = rd32(E1000_FCRTH);
	regs_buff[31] = rd32(E1000_FCRTV);

	/* Receive */
	regs_buff[32] = rd32(E1000_RCTL);
	regs_buff[33] = rd32(E1000_RXCSUM);
	regs_buff[34] = rd32(E1000_RLPML);
	regs_buff[35] = rd32(E1000_RFCTL);
	regs_buff[36] = rd32(E1000_MRQC);
	regs_buff[37] = rd32(E1000_VT_CTL);

	/* Transmit */
	regs_buff[38] = rd32(E1000_TCTL);
	regs_buff[39] = rd32(E1000_TCTL_EXT);
	regs_buff[40] = rd32(E1000_TIPG);
	regs_buff[41] = rd32(E1000_DTXCTL);

	/* Wake Up */
	regs_buff[42] = rd32(E1000_WUC);
	regs_buff[43] = rd32(E1000_WUFC);
	regs_buff[44] = rd32(E1000_WUS);
	regs_buff[45] = rd32(E1000_IPAV);
	regs_buff[46] = rd32(E1000_WUPL);

	/* MAC */
	regs_buff[47] = rd32(E1000_PCS_CFG0);
	regs_buff[48] = rd32(E1000_PCS_LCTL);
	regs_buff[49] = rd32(E1000_PCS_LSTAT);
	regs_buff[50] = rd32(E1000_PCS_ANADV);
	regs_buff[51] = rd32(E1000_PCS_LPAB);
	regs_buff[52] = rd32(E1000_PCS_NPTX);
	regs_buff[53] = rd32(E1000_PCS_LPABNP);

	/* Statistics */
	regs_buff[54] = adapter->stats.crcerrs;
	regs_buff[55] = adapter->stats.algnerrc;
	regs_buff[56] = adapter->stats.symerrs;
	regs_buff[57] = adapter->stats.rxerrc;
	regs_buff[58] = adapter->stats.mpc;
	regs_buff[59] = adapter->stats.scc;
	regs_buff[60] = adapter->stats.ecol;
	regs_buff[61] = adapter->stats.mcc;
	regs_buff[62] = adapter->stats.latecol;
	regs_buff[63] = adapter->stats.colc;
	regs_buff[64] = adapter->stats.dc;
	regs_buff[65] = adapter->stats.tncrs;
	regs_buff[66] = adapter->stats.sec;
	regs_buff[67] = adapter->stats.htdpmc;
	regs_buff[68] = adapter->stats.rlec;
	regs_buff[69] = adapter->stats.xonrxc;
	regs_buff[70] = adapter->stats.xontxc;
	regs_buff[71] = adapter->stats.xoffrxc;
	regs_buff[72] = adapter->stats.xofftxc;
	regs_buff[73] = adapter->stats.fcruc;
	regs_buff[74] = adapter->stats.prc64;
	regs_buff[75] = adapter->stats.prc127;
	regs_buff[76] = adapter->stats.prc255;
	regs_buff[77] = adapter->stats.prc511;
	regs_buff[78] = adapter->stats.prc1023;
	regs_buff[79] = adapter->stats.prc1522;
	regs_buff[80] = adapter->stats.gprc;
	regs_buff[81] = adapter->stats.bprc;
	regs_buff[82] = adapter->stats.mprc;
	regs_buff[83] = adapter->stats.gptc;
	regs_buff[84] = adapter->stats.gorc;
	regs_buff[86] = adapter->stats.gotc;
	regs_buff[88] = adapter->stats.rnbc;
	regs_buff[89] = adapter->stats.ruc;
	regs_buff[90] = adapter->stats.rfc;
	regs_buff[91] = adapter->stats.roc;
	regs_buff[92] = adapter->stats.rjc;
	regs_buff[93] = adapter->stats.mgprc;
	regs_buff[94] = adapter->stats.mgpdc;
	regs_buff[95] = adapter->stats.mgptc;
	regs_buff[96] = adapter->stats.tor;
	regs_buff[98] = adapter->stats.tot;
	regs_buff[100] = adapter->stats.tpr;
	regs_buff[101] = adapter->stats.tpt;
	regs_buff[102] = adapter->stats.ptc64;
	regs_buff[103] = adapter->stats.ptc127;
	regs_buff[104] = adapter->stats.ptc255;
	regs_buff[105] = adapter->stats.ptc511;
	regs_buff[106] = adapter->stats.ptc1023;
	regs_buff[107] = adapter->stats.ptc1522;
	regs_buff[108] = adapter->stats.mptc;
	regs_buff[109] = adapter->stats.bptc;
	regs_buff[110] = adapter->stats.tsctc;
	regs_buff[111] = adapter->stats.iac;
	regs_buff[112] = adapter->stats.rpthc;
	regs_buff[113] = adapter->stats.hgptc;
	regs_buff[114] = adapter->stats.hgorc;
	regs_buff[116] = adapter->stats.hgotc;
	regs_buff[118] = adapter->stats.lenerrs;
	regs_buff[119] = adapter->stats.scvpc;
	regs_buff[120] = adapter->stats.hrmpc;

	for (i = 0; i < 4; i++)
		regs_buff[121 + i] = rd32(E1000_SRRCTL(i));
	for (i = 0; i < 4; i++)
		regs_buff[125 + i] = rd32(E1000_PSRTYPE(i));
	for (i = 0; i < 4; i++)
		regs_buff[129 + i] = rd32(E1000_RDBAL(i));
	for (i = 0; i < 4; i++)
		regs_buff[133 + i] = rd32(E1000_RDBAH(i));
	for (i = 0; i < 4; i++)
		regs_buff[137 + i] = rd32(E1000_RDLEN(i));
	for (i = 0; i < 4; i++)
		regs_buff[141 + i] = rd32(E1000_RDH(i));
	for (i = 0; i < 4; i++)
		regs_buff[145 + i] = rd32(E1000_RDT(i));
	for (i = 0; i < 4; i++)
		regs_buff[149 + i] = rd32(E1000_RXDCTL(i));

	for (i = 0; i < 10; i++)
		regs_buff[153 + i] = rd32(E1000_EITR(i));
	for (i = 0; i < 8; i++)
		regs_buff[163 + i] = rd32(E1000_IMIR(i));
	for (i = 0; i < 8; i++)
		regs_buff[171 + i] = rd32(E1000_IMIREXT(i));
	for (i = 0; i < 16; i++)
		regs_buff[179 + i] = rd32(E1000_RAL(i));
	for (i = 0; i < 16; i++)
		regs_buff[195 + i] = rd32(E1000_RAH(i));

	for (i = 0; i < 4; i++)
		regs_buff[211 + i] = rd32(E1000_TDBAL(i));
	for (i = 0; i < 4; i++)
		regs_buff[215 + i] = rd32(E1000_TDBAH(i));
	for (i = 0; i < 4; i++)
		regs_buff[219 + i] = rd32(E1000_TDLEN(i));
	for (i = 0; i < 4; i++)
		regs_buff[223 + i] = rd32(E1000_TDH(i));
	for (i = 0; i < 4; i++)
		regs_buff[227 + i] = rd32(E1000_TDT(i));
	for (i = 0; i < 4; i++)
		regs_buff[231 + i] = rd32(E1000_TXDCTL(i));
	for (i = 0; i < 4; i++)
		regs_buff[235 + i] = rd32(E1000_TDWBAL(i));
	for (i = 0; i < 4; i++)
		regs_buff[239 + i] = rd32(E1000_TDWBAH(i));
	for (i = 0; i < 4; i++)
		regs_buff[243 + i] = rd32(E1000_DCA_TXCTRL(i));

	for (i = 0; i < 4; i++)
		regs_buff[247 + i] = rd32(E1000_IP4AT_REG(i));
	for (i = 0; i < 4; i++)
		regs_buff[251 + i] = rd32(E1000_IP6AT_REG(i));
	for (i = 0; i < 32; i++)
		regs_buff[255 + i] = rd32(E1000_WUPM_REG(i));
	for (i = 0; i < 128; i++)
		regs_buff[287 + i] = rd32(E1000_FFMT_REG(i));
	for (i = 0; i < 128; i++)
		regs_buff[415 + i] = rd32(E1000_FFVT_REG(i));
	for (i = 0; i < 4; i++)
		regs_buff[543 + i] = rd32(E1000_FFLT_REG(i));

	regs_buff[547] = rd32(E1000_TDFH);
	regs_buff[548] = rd32(E1000_TDFT);
	regs_buff[549] = rd32(E1000_TDFHS);
	regs_buff[550] = rd32(E1000_TDFPC);

	if (hw->mac.type > e1000_82580) {
		regs_buff[551] = adapter->stats.o2bgptc;
		regs_buff[552] = adapter->stats.b2ospc;
		regs_buff[553] = adapter->stats.o2bspc;
		regs_buff[554] = adapter->stats.b2ogprc;
	}

	if (hw->mac.type != e1000_82576)
		return;
	for (i = 0; i < 12; i++)
		regs_buff[555 + i] = rd32(E1000_SRRCTL(i + 4));
	for (i = 0; i < 4; i++)
		regs_buff[567 + i] = rd32(E1000_PSRTYPE(i + 4));
	for (i = 0; i < 12; i++)
		regs_buff[571 + i] = rd32(E1000_RDBAL(i + 4));
	for (i = 0; i < 12; i++)
		regs_buff[583 + i] = rd32(E1000_RDBAH(i + 4));
	for (i = 0; i < 12; i++)
		regs_buff[595 + i] = rd32(E1000_RDLEN(i + 4));
	for (i = 0; i < 12; i++)
		regs_buff[607 + i] = rd32(E1000_RDH(i + 4));
	for (i = 0; i < 12; i++)
		regs_buff[619 + i] = rd32(E1000_RDT(i + 4));
	for (i = 0; i < 12; i++)
		regs_buff[631 + i] = rd32(E1000_RXDCTL(i + 4));

	for (i = 0; i < 12; i++)
		regs_buff[643 + i] = rd32(E1000_TDBAL(i + 4));
	for (i = 0; i < 12; i++)
		regs_buff[655 + i] = rd32(E1000_TDBAH(i + 4));
	for (i = 0; i < 12; i++)
		regs_buff[667 + i] = rd32(E1000_TDLEN(i + 4));
	for (i = 0; i < 12; i++)
		regs_buff[679 + i] = rd32(E1000_TDH(i + 4));
	for (i = 0; i < 12; i++)
		regs_buff[691 + i] = rd32(E1000_TDT(i + 4));
	for (i = 0; i < 12; i++)
		regs_buff[703 + i] = rd32(E1000_TXDCTL(i + 4));
	for (i = 0; i < 12; i++)
		regs_buff[715 + i] = rd32(E1000_TDWBAL(i + 4));
	for (i = 0; i < 12; i++)
		regs_buff[727 + i] = rd32(E1000_TDWBAH(i + 4));
}