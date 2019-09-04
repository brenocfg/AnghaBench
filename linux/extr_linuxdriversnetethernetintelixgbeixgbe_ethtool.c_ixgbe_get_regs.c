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
typedef  int u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int type; } ;
struct ixgbe_hw {int revision_id; int device_id; TYPE_1__ mac; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; } ;
struct ethtool_regs {int version; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_AIS ; 
 int /*<<< orphan*/  IXGBE_ANLP1 ; 
 int /*<<< orphan*/  IXGBE_ANLP2 ; 
 int /*<<< orphan*/  IXGBE_APAE ; 
 int /*<<< orphan*/  IXGBE_ARD ; 
 int /*<<< orphan*/  IXGBE_ATLASCTL ; 
 int /*<<< orphan*/  IXGBE_AUTOC ; 
 int /*<<< orphan*/  IXGBE_AUTOC2 ; 
 int /*<<< orphan*/  IXGBE_AUTOC3 ; 
 int /*<<< orphan*/  IXGBE_CTRL ; 
 int /*<<< orphan*/  IXGBE_CTRL_EXT ; 
 int /*<<< orphan*/  IXGBE_DCA_RXCTRL (int) ; 
 int /*<<< orphan*/  IXGBE_DCA_TXCTRL (int) ; 
 int /*<<< orphan*/  IXGBE_DPMCS ; 
 int /*<<< orphan*/  IXGBE_DROPEN ; 
 int /*<<< orphan*/  IXGBE_DTXCTL ; 
 int /*<<< orphan*/  IXGBE_EEC (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_EEMNGCTL ; 
 int /*<<< orphan*/  IXGBE_EEMNGDATA ; 
 int /*<<< orphan*/  IXGBE_EERD ; 
 int /*<<< orphan*/  IXGBE_EIAC ; 
 int /*<<< orphan*/  IXGBE_EIAM ; 
 int /*<<< orphan*/  IXGBE_EICS ; 
 int /*<<< orphan*/  IXGBE_EIMC ; 
 int /*<<< orphan*/  IXGBE_EIMS ; 
 int /*<<< orphan*/  IXGBE_EITR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_EODSDP ; 
 int /*<<< orphan*/  IXGBE_ESDP ; 
 int /*<<< orphan*/  IXGBE_FCRTH (int) ; 
 int /*<<< orphan*/  IXGBE_FCRTH_82599 (int) ; 
 int /*<<< orphan*/  IXGBE_FCRTL (int) ; 
 int /*<<< orphan*/  IXGBE_FCRTL_82599 (int) ; 
 int /*<<< orphan*/  IXGBE_FCRTV ; 
 int /*<<< orphan*/  IXGBE_FCTRL ; 
 int /*<<< orphan*/  IXGBE_FCTTV (int) ; 
 int /*<<< orphan*/  IXGBE_FHFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_FLA (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_FLMNGCNT ; 
 int /*<<< orphan*/  IXGBE_FLMNGCTL ; 
 int /*<<< orphan*/  IXGBE_FLMNGDATA ; 
 int /*<<< orphan*/  IXGBE_FLOP ; 
 int /*<<< orphan*/  IXGBE_FRTIMER ; 
 int IXGBE_GET_STAT (struct ixgbe_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_GPIE ; 
 int /*<<< orphan*/  IXGBE_GRC (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_HLREG0 ; 
 int /*<<< orphan*/  IXGBE_HLREG1 ; 
 int /*<<< orphan*/  IXGBE_IMIR (int) ; 
 int /*<<< orphan*/  IXGBE_IMIREXT (int) ; 
 int /*<<< orphan*/  IXGBE_IMIRVP ; 
 int /*<<< orphan*/  IXGBE_IP4AT ; 
 int /*<<< orphan*/  IXGBE_IP6AT ; 
 int /*<<< orphan*/  IXGBE_IPAV ; 
 int /*<<< orphan*/  IXGBE_IVAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_LEDCTL ; 
 int /*<<< orphan*/  IXGBE_LINKS ; 
 int /*<<< orphan*/  IXGBE_MACA ; 
 int /*<<< orphan*/  IXGBE_MACS ; 
 int /*<<< orphan*/  IXGBE_MCSTCTRL ; 
 int /*<<< orphan*/  IXGBE_MDFTC1 ; 
 int /*<<< orphan*/  IXGBE_MDFTC2 ; 
 int /*<<< orphan*/  IXGBE_MDFTFIFO1 ; 
 int /*<<< orphan*/  IXGBE_MDFTFIFO2 ; 
 int /*<<< orphan*/  IXGBE_MDFTS ; 
 int /*<<< orphan*/  IXGBE_MFLCN ; 
 int /*<<< orphan*/  IXGBE_MHADD ; 
 int /*<<< orphan*/  IXGBE_MLADD ; 
 int /*<<< orphan*/  IXGBE_MNGTXMAP ; 
 int /*<<< orphan*/  IXGBE_MRQC ; 
 int /*<<< orphan*/  IXGBE_MSCA ; 
 int /*<<< orphan*/  IXGBE_MSIXPBA ; 
 int /*<<< orphan*/  IXGBE_MSIXT ; 
 int /*<<< orphan*/  IXGBE_MSRWD ; 
 int /*<<< orphan*/  IXGBE_PAP ; 
 int /*<<< orphan*/  IXGBE_PBACL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_PBRXECC ; 
 int /*<<< orphan*/  IXGBE_PBTXECC ; 
 int /*<<< orphan*/  IXGBE_PCIEECCCTL ; 
 int /*<<< orphan*/  IXGBE_PCIE_DIAG (int) ; 
 int /*<<< orphan*/  IXGBE_PCS1GANA ; 
 int /*<<< orphan*/  IXGBE_PCS1GANLP ; 
 int /*<<< orphan*/  IXGBE_PCS1GANLPNP ; 
 int /*<<< orphan*/  IXGBE_PCS1GANNP ; 
 int /*<<< orphan*/  IXGBE_PCS1GCFIG ; 
 int /*<<< orphan*/  IXGBE_PCS1GDBG0 ; 
 int /*<<< orphan*/  IXGBE_PCS1GDBG1 ; 
 int /*<<< orphan*/  IXGBE_PCS1GLCTL ; 
 int /*<<< orphan*/  IXGBE_PCS1GLSTA ; 
 int /*<<< orphan*/  IXGBE_PCSS1 ; 
 int /*<<< orphan*/  IXGBE_PCSS2 ; 
 int /*<<< orphan*/  IXGBE_PDPMCS ; 
 int /*<<< orphan*/  IXGBE_PFCTOP ; 
 int /*<<< orphan*/  IXGBE_PSRTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_RAH (int) ; 
 int /*<<< orphan*/  IXGBE_RAL (int) ; 
 int /*<<< orphan*/  IXGBE_RDBAH (int) ; 
 int /*<<< orphan*/  IXGBE_RDBAL (int) ; 
 int /*<<< orphan*/  IXGBE_RDH (int) ; 
 int /*<<< orphan*/  IXGBE_RDHMPN ; 
 int /*<<< orphan*/  IXGBE_RDLEN (int) ; 
 int /*<<< orphan*/  IXGBE_RDPROBE ; 
 int /*<<< orphan*/  IXGBE_RDRXCTL ; 
 int /*<<< orphan*/  IXGBE_RDSTAT (int) ; 
 int /*<<< orphan*/  IXGBE_RDSTATCTL ; 
 int /*<<< orphan*/  IXGBE_RDT (int) ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int IXGBE_REGS_LEN ; 
 int /*<<< orphan*/  IXGBE_RFCTL ; 
 int /*<<< orphan*/  IXGBE_RFVAL ; 
 int /*<<< orphan*/  IXGBE_RIC_DW (int) ; 
 int /*<<< orphan*/  IXGBE_RMCS ; 
 int /*<<< orphan*/  IXGBE_RT2CR (int) ; 
 int /*<<< orphan*/  IXGBE_RT2SR (int) ; 
 int /*<<< orphan*/  IXGBE_RTRPCS ; 
 int /*<<< orphan*/  IXGBE_RTRPT4C (int) ; 
 int /*<<< orphan*/  IXGBE_RTRPT4S (int) ; 
 int /*<<< orphan*/  IXGBE_RTRUP2TC ; 
 int /*<<< orphan*/  IXGBE_RTTBCNRD ; 
 int /*<<< orphan*/  IXGBE_RTTBCNRM ; 
 int /*<<< orphan*/  IXGBE_RTTDCS ; 
 int /*<<< orphan*/  IXGBE_RTTDT2C (int) ; 
 int /*<<< orphan*/  IXGBE_RTTDT2S (int) ; 
 int /*<<< orphan*/  IXGBE_RTTQCNCR ; 
 int /*<<< orphan*/  IXGBE_RTTQCNTG ; 
 int /*<<< orphan*/  IXGBE_RTTUP2TC ; 
 int /*<<< orphan*/  IXGBE_RUPPBMR ; 
 int /*<<< orphan*/  IXGBE_RXBUFCTRL ; 
 int /*<<< orphan*/  IXGBE_RXBUFDATA (int) ; 
 int /*<<< orphan*/  IXGBE_RXCSUM ; 
 int /*<<< orphan*/  IXGBE_RXCTRL ; 
 int /*<<< orphan*/  IXGBE_RXDCTL (int) ; 
 int /*<<< orphan*/  IXGBE_RXPBSIZE (int) ; 
 int /*<<< orphan*/  IXGBE_SECRXCTRL ; 
 int /*<<< orphan*/  IXGBE_SECRXSTAT ; 
 int /*<<< orphan*/  IXGBE_SECTXBUFFAF ; 
 int /*<<< orphan*/  IXGBE_SECTXCTRL ; 
 int /*<<< orphan*/  IXGBE_SECTXMINIFG ; 
 int /*<<< orphan*/  IXGBE_SECTXSTAT ; 
 int /*<<< orphan*/  IXGBE_SERDESC ; 
 int /*<<< orphan*/  IXGBE_SRRCTL (int) ; 
 int /*<<< orphan*/  IXGBE_STATUS ; 
 int /*<<< orphan*/  IXGBE_TCPTIMER ; 
 int /*<<< orphan*/  IXGBE_TDBAH (int) ; 
 int /*<<< orphan*/  IXGBE_TDBAL (int) ; 
 int /*<<< orphan*/  IXGBE_TDH (int) ; 
 int /*<<< orphan*/  IXGBE_TDHMPN ; 
 int /*<<< orphan*/  IXGBE_TDLEN (int) ; 
 int /*<<< orphan*/  IXGBE_TDPROBE ; 
 int /*<<< orphan*/  IXGBE_TDPT2TCCR (int) ; 
 int /*<<< orphan*/  IXGBE_TDPT2TCSR (int) ; 
 int /*<<< orphan*/  IXGBE_TDSTAT (int) ; 
 int /*<<< orphan*/  IXGBE_TDSTATCTL ; 
 int /*<<< orphan*/  IXGBE_TDT (int) ; 
 int /*<<< orphan*/  IXGBE_TDTQ2TCCR (int) ; 
 int /*<<< orphan*/  IXGBE_TDTQ2TCSR (int) ; 
 int /*<<< orphan*/  IXGBE_TDWBAH (int) ; 
 int /*<<< orphan*/  IXGBE_TDWBAL (int) ; 
 int /*<<< orphan*/  IXGBE_TFCS ; 
 int /*<<< orphan*/  IXGBE_TIC_DW (int) ; 
 int /*<<< orphan*/  IXGBE_TIPG ; 
 int /*<<< orphan*/  IXGBE_TREG ; 
 int /*<<< orphan*/  IXGBE_TXBUFCTRL ; 
 int /*<<< orphan*/  IXGBE_TXBUFDATA (int) ; 
 int /*<<< orphan*/  IXGBE_TXDCTL (int) ; 
 int /*<<< orphan*/  IXGBE_TXLLQ (int) ; 
 int /*<<< orphan*/  IXGBE_TXPBSIZE (int) ; 
 int /*<<< orphan*/  IXGBE_VLNCTRL ; 
 int /*<<< orphan*/  IXGBE_VMD_CTL ; 
 int /*<<< orphan*/  IXGBE_WUC ; 
 int /*<<< orphan*/  IXGBE_WUFC ; 
 int /*<<< orphan*/  IXGBE_WUPL ; 
 int /*<<< orphan*/  IXGBE_WUPM ; 
 int /*<<< orphan*/  IXGBE_WUS ; 
 int /*<<< orphan*/  IXGBE_XPCSS ; 
 int /*<<< orphan*/  bprc ; 
 int /*<<< orphan*/  bptc ; 
 int /*<<< orphan*/  crcerrs ; 
 int /*<<< orphan*/  errbc ; 
 int /*<<< orphan*/  gorc ; 
 int /*<<< orphan*/  gotc ; 
 int /*<<< orphan*/  gprc ; 
 int /*<<< orphan*/  gptc ; 
 int /*<<< orphan*/  illerrc ; 
#define  ixgbe_mac_82598EB 133 
#define  ixgbe_mac_82599EB 132 
#define  ixgbe_mac_X540 131 
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_x 129 
#define  ixgbe_mac_x550em_a 128 
 int /*<<< orphan*/  lxoffrxc ; 
 int /*<<< orphan*/  lxofftxc ; 
 int /*<<< orphan*/  lxonrxc ; 
 int /*<<< orphan*/  lxontxc ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlfc ; 
 int /*<<< orphan*/  mngpdc ; 
 int /*<<< orphan*/  mngprc ; 
 int /*<<< orphan*/  mngptc ; 
 int /*<<< orphan*/ * mpc ; 
 int /*<<< orphan*/  mprc ; 
 int /*<<< orphan*/  mptc ; 
 int /*<<< orphan*/  mrfc ; 
 int /*<<< orphan*/  mspdc ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  prc1023 ; 
 int /*<<< orphan*/  prc127 ; 
 int /*<<< orphan*/  prc1522 ; 
 int /*<<< orphan*/  prc255 ; 
 int /*<<< orphan*/  prc511 ; 
 int /*<<< orphan*/  prc64 ; 
 int /*<<< orphan*/  ptc1023 ; 
 int /*<<< orphan*/  ptc127 ; 
 int /*<<< orphan*/  ptc1522 ; 
 int /*<<< orphan*/  ptc255 ; 
 int /*<<< orphan*/  ptc511 ; 
 int /*<<< orphan*/  ptc64 ; 
 int /*<<< orphan*/ * pxoffrxc ; 
 int /*<<< orphan*/ * pxofftxc ; 
 int /*<<< orphan*/ * pxonrxc ; 
 int /*<<< orphan*/ * pxontxc ; 
 int /*<<< orphan*/ * qbrc ; 
 int /*<<< orphan*/ * qbtc ; 
 int /*<<< orphan*/ * qprc ; 
 int /*<<< orphan*/ * qptc ; 
 int /*<<< orphan*/  rfc ; 
 int /*<<< orphan*/  rjc ; 
 int /*<<< orphan*/  rlec ; 
 int /*<<< orphan*/ * rnbc ; 
 int /*<<< orphan*/  roc ; 
 int /*<<< orphan*/  ruc ; 
 int /*<<< orphan*/  tor ; 
 int /*<<< orphan*/  tpr ; 
 int /*<<< orphan*/  tpt ; 
 int /*<<< orphan*/  xec ; 

__attribute__((used)) static void ixgbe_get_regs(struct net_device *netdev,
			   struct ethtool_regs *regs, void *p)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	struct ixgbe_hw *hw = &adapter->hw;
	u32 *regs_buff = p;
	u8 i;

	memset(p, 0, IXGBE_REGS_LEN * sizeof(u32));

	regs->version = hw->mac.type << 24 | hw->revision_id << 16 |
			hw->device_id;

	/* General Registers */
	regs_buff[0] = IXGBE_READ_REG(hw, IXGBE_CTRL);
	regs_buff[1] = IXGBE_READ_REG(hw, IXGBE_STATUS);
	regs_buff[2] = IXGBE_READ_REG(hw, IXGBE_CTRL_EXT);
	regs_buff[3] = IXGBE_READ_REG(hw, IXGBE_ESDP);
	regs_buff[4] = IXGBE_READ_REG(hw, IXGBE_EODSDP);
	regs_buff[5] = IXGBE_READ_REG(hw, IXGBE_LEDCTL);
	regs_buff[6] = IXGBE_READ_REG(hw, IXGBE_FRTIMER);
	regs_buff[7] = IXGBE_READ_REG(hw, IXGBE_TCPTIMER);

	/* NVM Register */
	regs_buff[8] = IXGBE_READ_REG(hw, IXGBE_EEC(hw));
	regs_buff[9] = IXGBE_READ_REG(hw, IXGBE_EERD);
	regs_buff[10] = IXGBE_READ_REG(hw, IXGBE_FLA(hw));
	regs_buff[11] = IXGBE_READ_REG(hw, IXGBE_EEMNGCTL);
	regs_buff[12] = IXGBE_READ_REG(hw, IXGBE_EEMNGDATA);
	regs_buff[13] = IXGBE_READ_REG(hw, IXGBE_FLMNGCTL);
	regs_buff[14] = IXGBE_READ_REG(hw, IXGBE_FLMNGDATA);
	regs_buff[15] = IXGBE_READ_REG(hw, IXGBE_FLMNGCNT);
	regs_buff[16] = IXGBE_READ_REG(hw, IXGBE_FLOP);
	regs_buff[17] = IXGBE_READ_REG(hw, IXGBE_GRC(hw));

	/* Interrupt */
	/* don't read EICR because it can clear interrupt causes, instead
	 * read EICS which is a shadow but doesn't clear EICR */
	regs_buff[18] = IXGBE_READ_REG(hw, IXGBE_EICS);
	regs_buff[19] = IXGBE_READ_REG(hw, IXGBE_EICS);
	regs_buff[20] = IXGBE_READ_REG(hw, IXGBE_EIMS);
	regs_buff[21] = IXGBE_READ_REG(hw, IXGBE_EIMC);
	regs_buff[22] = IXGBE_READ_REG(hw, IXGBE_EIAC);
	regs_buff[23] = IXGBE_READ_REG(hw, IXGBE_EIAM);
	regs_buff[24] = IXGBE_READ_REG(hw, IXGBE_EITR(0));
	regs_buff[25] = IXGBE_READ_REG(hw, IXGBE_IVAR(0));
	regs_buff[26] = IXGBE_READ_REG(hw, IXGBE_MSIXT);
	regs_buff[27] = IXGBE_READ_REG(hw, IXGBE_MSIXPBA);
	regs_buff[28] = IXGBE_READ_REG(hw, IXGBE_PBACL(0));
	regs_buff[29] = IXGBE_READ_REG(hw, IXGBE_GPIE);

	/* Flow Control */
	regs_buff[30] = IXGBE_READ_REG(hw, IXGBE_PFCTOP);
	for (i = 0; i < 4; i++)
		regs_buff[31 + i] = IXGBE_READ_REG(hw, IXGBE_FCTTV(i));
	for (i = 0; i < 8; i++) {
		switch (hw->mac.type) {
		case ixgbe_mac_82598EB:
			regs_buff[35 + i] = IXGBE_READ_REG(hw, IXGBE_FCRTL(i));
			regs_buff[43 + i] = IXGBE_READ_REG(hw, IXGBE_FCRTH(i));
			break;
		case ixgbe_mac_82599EB:
		case ixgbe_mac_X540:
		case ixgbe_mac_X550:
		case ixgbe_mac_X550EM_x:
		case ixgbe_mac_x550em_a:
			regs_buff[35 + i] = IXGBE_READ_REG(hw, IXGBE_FCRTL_82599(i));
			regs_buff[43 + i] = IXGBE_READ_REG(hw, IXGBE_FCRTH_82599(i));
			break;
		default:
			break;
		}
	}
	regs_buff[51] = IXGBE_READ_REG(hw, IXGBE_FCRTV);
	regs_buff[52] = IXGBE_READ_REG(hw, IXGBE_TFCS);

	/* Receive DMA */
	for (i = 0; i < 64; i++)
		regs_buff[53 + i] = IXGBE_READ_REG(hw, IXGBE_RDBAL(i));
	for (i = 0; i < 64; i++)
		regs_buff[117 + i] = IXGBE_READ_REG(hw, IXGBE_RDBAH(i));
	for (i = 0; i < 64; i++)
		regs_buff[181 + i] = IXGBE_READ_REG(hw, IXGBE_RDLEN(i));
	for (i = 0; i < 64; i++)
		regs_buff[245 + i] = IXGBE_READ_REG(hw, IXGBE_RDH(i));
	for (i = 0; i < 64; i++)
		regs_buff[309 + i] = IXGBE_READ_REG(hw, IXGBE_RDT(i));
	for (i = 0; i < 64; i++)
		regs_buff[373 + i] = IXGBE_READ_REG(hw, IXGBE_RXDCTL(i));
	for (i = 0; i < 16; i++)
		regs_buff[437 + i] = IXGBE_READ_REG(hw, IXGBE_SRRCTL(i));
	for (i = 0; i < 16; i++)
		regs_buff[453 + i] = IXGBE_READ_REG(hw, IXGBE_DCA_RXCTRL(i));
	regs_buff[469] = IXGBE_READ_REG(hw, IXGBE_RDRXCTL);
	for (i = 0; i < 8; i++)
		regs_buff[470 + i] = IXGBE_READ_REG(hw, IXGBE_RXPBSIZE(i));
	regs_buff[478] = IXGBE_READ_REG(hw, IXGBE_RXCTRL);
	regs_buff[479] = IXGBE_READ_REG(hw, IXGBE_DROPEN);

	/* Receive */
	regs_buff[480] = IXGBE_READ_REG(hw, IXGBE_RXCSUM);
	regs_buff[481] = IXGBE_READ_REG(hw, IXGBE_RFCTL);
	for (i = 0; i < 16; i++)
		regs_buff[482 + i] = IXGBE_READ_REG(hw, IXGBE_RAL(i));
	for (i = 0; i < 16; i++)
		regs_buff[498 + i] = IXGBE_READ_REG(hw, IXGBE_RAH(i));
	regs_buff[514] = IXGBE_READ_REG(hw, IXGBE_PSRTYPE(0));
	regs_buff[515] = IXGBE_READ_REG(hw, IXGBE_FCTRL);
	regs_buff[516] = IXGBE_READ_REG(hw, IXGBE_VLNCTRL);
	regs_buff[517] = IXGBE_READ_REG(hw, IXGBE_MCSTCTRL);
	regs_buff[518] = IXGBE_READ_REG(hw, IXGBE_MRQC);
	regs_buff[519] = IXGBE_READ_REG(hw, IXGBE_VMD_CTL);
	for (i = 0; i < 8; i++)
		regs_buff[520 + i] = IXGBE_READ_REG(hw, IXGBE_IMIR(i));
	for (i = 0; i < 8; i++)
		regs_buff[528 + i] = IXGBE_READ_REG(hw, IXGBE_IMIREXT(i));
	regs_buff[536] = IXGBE_READ_REG(hw, IXGBE_IMIRVP);

	/* Transmit */
	for (i = 0; i < 32; i++)
		regs_buff[537 + i] = IXGBE_READ_REG(hw, IXGBE_TDBAL(i));
	for (i = 0; i < 32; i++)
		regs_buff[569 + i] = IXGBE_READ_REG(hw, IXGBE_TDBAH(i));
	for (i = 0; i < 32; i++)
		regs_buff[601 + i] = IXGBE_READ_REG(hw, IXGBE_TDLEN(i));
	for (i = 0; i < 32; i++)
		regs_buff[633 + i] = IXGBE_READ_REG(hw, IXGBE_TDH(i));
	for (i = 0; i < 32; i++)
		regs_buff[665 + i] = IXGBE_READ_REG(hw, IXGBE_TDT(i));
	for (i = 0; i < 32; i++)
		regs_buff[697 + i] = IXGBE_READ_REG(hw, IXGBE_TXDCTL(i));
	for (i = 0; i < 32; i++)
		regs_buff[729 + i] = IXGBE_READ_REG(hw, IXGBE_TDWBAL(i));
	for (i = 0; i < 32; i++)
		regs_buff[761 + i] = IXGBE_READ_REG(hw, IXGBE_TDWBAH(i));
	regs_buff[793] = IXGBE_READ_REG(hw, IXGBE_DTXCTL);
	for (i = 0; i < 16; i++)
		regs_buff[794 + i] = IXGBE_READ_REG(hw, IXGBE_DCA_TXCTRL(i));
	regs_buff[810] = IXGBE_READ_REG(hw, IXGBE_TIPG);
	for (i = 0; i < 8; i++)
		regs_buff[811 + i] = IXGBE_READ_REG(hw, IXGBE_TXPBSIZE(i));
	regs_buff[819] = IXGBE_READ_REG(hw, IXGBE_MNGTXMAP);

	/* Wake Up */
	regs_buff[820] = IXGBE_READ_REG(hw, IXGBE_WUC);
	regs_buff[821] = IXGBE_READ_REG(hw, IXGBE_WUFC);
	regs_buff[822] = IXGBE_READ_REG(hw, IXGBE_WUS);
	regs_buff[823] = IXGBE_READ_REG(hw, IXGBE_IPAV);
	regs_buff[824] = IXGBE_READ_REG(hw, IXGBE_IP4AT);
	regs_buff[825] = IXGBE_READ_REG(hw, IXGBE_IP6AT);
	regs_buff[826] = IXGBE_READ_REG(hw, IXGBE_WUPL);
	regs_buff[827] = IXGBE_READ_REG(hw, IXGBE_WUPM);
	regs_buff[828] = IXGBE_READ_REG(hw, IXGBE_FHFT(0));

	/* DCB */
	regs_buff[829] = IXGBE_READ_REG(hw, IXGBE_RMCS);   /* same as FCCFG  */
	regs_buff[831] = IXGBE_READ_REG(hw, IXGBE_PDPMCS); /* same as RTTPCS */

	switch (hw->mac.type) {
	case ixgbe_mac_82598EB:
		regs_buff[830] = IXGBE_READ_REG(hw, IXGBE_DPMCS);
		regs_buff[832] = IXGBE_READ_REG(hw, IXGBE_RUPPBMR);
		for (i = 0; i < 8; i++)
			regs_buff[833 + i] =
				IXGBE_READ_REG(hw, IXGBE_RT2CR(i));
		for (i = 0; i < 8; i++)
			regs_buff[841 + i] =
				IXGBE_READ_REG(hw, IXGBE_RT2SR(i));
		for (i = 0; i < 8; i++)
			regs_buff[849 + i] =
				IXGBE_READ_REG(hw, IXGBE_TDTQ2TCCR(i));
		for (i = 0; i < 8; i++)
			regs_buff[857 + i] =
				IXGBE_READ_REG(hw, IXGBE_TDTQ2TCSR(i));
		break;
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_x550em_a:
		regs_buff[830] = IXGBE_READ_REG(hw, IXGBE_RTTDCS);
		regs_buff[832] = IXGBE_READ_REG(hw, IXGBE_RTRPCS);
		for (i = 0; i < 8; i++)
			regs_buff[833 + i] =
				IXGBE_READ_REG(hw, IXGBE_RTRPT4C(i));
		for (i = 0; i < 8; i++)
			regs_buff[841 + i] =
				IXGBE_READ_REG(hw, IXGBE_RTRPT4S(i));
		for (i = 0; i < 8; i++)
			regs_buff[849 + i] =
				IXGBE_READ_REG(hw, IXGBE_RTTDT2C(i));
		for (i = 0; i < 8; i++)
			regs_buff[857 + i] =
				IXGBE_READ_REG(hw, IXGBE_RTTDT2S(i));
		break;
	default:
		break;
	}

	for (i = 0; i < 8; i++)
		regs_buff[865 + i] =
		IXGBE_READ_REG(hw, IXGBE_TDPT2TCCR(i)); /* same as RTTPT2C */
	for (i = 0; i < 8; i++)
		regs_buff[873 + i] =
		IXGBE_READ_REG(hw, IXGBE_TDPT2TCSR(i)); /* same as RTTPT2S */

	/* Statistics */
	regs_buff[881] = IXGBE_GET_STAT(adapter, crcerrs);
	regs_buff[882] = IXGBE_GET_STAT(adapter, illerrc);
	regs_buff[883] = IXGBE_GET_STAT(adapter, errbc);
	regs_buff[884] = IXGBE_GET_STAT(adapter, mspdc);
	for (i = 0; i < 8; i++)
		regs_buff[885 + i] = IXGBE_GET_STAT(adapter, mpc[i]);
	regs_buff[893] = IXGBE_GET_STAT(adapter, mlfc);
	regs_buff[894] = IXGBE_GET_STAT(adapter, mrfc);
	regs_buff[895] = IXGBE_GET_STAT(adapter, rlec);
	regs_buff[896] = IXGBE_GET_STAT(adapter, lxontxc);
	regs_buff[897] = IXGBE_GET_STAT(adapter, lxonrxc);
	regs_buff[898] = IXGBE_GET_STAT(adapter, lxofftxc);
	regs_buff[899] = IXGBE_GET_STAT(adapter, lxoffrxc);
	for (i = 0; i < 8; i++)
		regs_buff[900 + i] = IXGBE_GET_STAT(adapter, pxontxc[i]);
	for (i = 0; i < 8; i++)
		regs_buff[908 + i] = IXGBE_GET_STAT(adapter, pxonrxc[i]);
	for (i = 0; i < 8; i++)
		regs_buff[916 + i] = IXGBE_GET_STAT(adapter, pxofftxc[i]);
	for (i = 0; i < 8; i++)
		regs_buff[924 + i] = IXGBE_GET_STAT(adapter, pxoffrxc[i]);
	regs_buff[932] = IXGBE_GET_STAT(adapter, prc64);
	regs_buff[933] = IXGBE_GET_STAT(adapter, prc127);
	regs_buff[934] = IXGBE_GET_STAT(adapter, prc255);
	regs_buff[935] = IXGBE_GET_STAT(adapter, prc511);
	regs_buff[936] = IXGBE_GET_STAT(adapter, prc1023);
	regs_buff[937] = IXGBE_GET_STAT(adapter, prc1522);
	regs_buff[938] = IXGBE_GET_STAT(adapter, gprc);
	regs_buff[939] = IXGBE_GET_STAT(adapter, bprc);
	regs_buff[940] = IXGBE_GET_STAT(adapter, mprc);
	regs_buff[941] = IXGBE_GET_STAT(adapter, gptc);
	regs_buff[942] = (u32)IXGBE_GET_STAT(adapter, gorc);
	regs_buff[943] = (u32)(IXGBE_GET_STAT(adapter, gorc) >> 32);
	regs_buff[944] = (u32)IXGBE_GET_STAT(adapter, gotc);
	regs_buff[945] = (u32)(IXGBE_GET_STAT(adapter, gotc) >> 32);
	for (i = 0; i < 8; i++)
		regs_buff[946 + i] = IXGBE_GET_STAT(adapter, rnbc[i]);
	regs_buff[954] = IXGBE_GET_STAT(adapter, ruc);
	regs_buff[955] = IXGBE_GET_STAT(adapter, rfc);
	regs_buff[956] = IXGBE_GET_STAT(adapter, roc);
	regs_buff[957] = IXGBE_GET_STAT(adapter, rjc);
	regs_buff[958] = IXGBE_GET_STAT(adapter, mngprc);
	regs_buff[959] = IXGBE_GET_STAT(adapter, mngpdc);
	regs_buff[960] = IXGBE_GET_STAT(adapter, mngptc);
	regs_buff[961] = (u32)IXGBE_GET_STAT(adapter, tor);
	regs_buff[962] = (u32)(IXGBE_GET_STAT(adapter, tor) >> 32);
	regs_buff[963] = IXGBE_GET_STAT(adapter, tpr);
	regs_buff[964] = IXGBE_GET_STAT(adapter, tpt);
	regs_buff[965] = IXGBE_GET_STAT(adapter, ptc64);
	regs_buff[966] = IXGBE_GET_STAT(adapter, ptc127);
	regs_buff[967] = IXGBE_GET_STAT(adapter, ptc255);
	regs_buff[968] = IXGBE_GET_STAT(adapter, ptc511);
	regs_buff[969] = IXGBE_GET_STAT(adapter, ptc1023);
	regs_buff[970] = IXGBE_GET_STAT(adapter, ptc1522);
	regs_buff[971] = IXGBE_GET_STAT(adapter, mptc);
	regs_buff[972] = IXGBE_GET_STAT(adapter, bptc);
	regs_buff[973] = IXGBE_GET_STAT(adapter, xec);
	for (i = 0; i < 16; i++)
		regs_buff[974 + i] = IXGBE_GET_STAT(adapter, qprc[i]);
	for (i = 0; i < 16; i++)
		regs_buff[990 + i] = IXGBE_GET_STAT(adapter, qptc[i]);
	for (i = 0; i < 16; i++)
		regs_buff[1006 + i] = IXGBE_GET_STAT(adapter, qbrc[i]);
	for (i = 0; i < 16; i++)
		regs_buff[1022 + i] = IXGBE_GET_STAT(adapter, qbtc[i]);

	/* MAC */
	regs_buff[1038] = IXGBE_READ_REG(hw, IXGBE_PCS1GCFIG);
	regs_buff[1039] = IXGBE_READ_REG(hw, IXGBE_PCS1GLCTL);
	regs_buff[1040] = IXGBE_READ_REG(hw, IXGBE_PCS1GLSTA);
	regs_buff[1041] = IXGBE_READ_REG(hw, IXGBE_PCS1GDBG0);
	regs_buff[1042] = IXGBE_READ_REG(hw, IXGBE_PCS1GDBG1);
	regs_buff[1043] = IXGBE_READ_REG(hw, IXGBE_PCS1GANA);
	regs_buff[1044] = IXGBE_READ_REG(hw, IXGBE_PCS1GANLP);
	regs_buff[1045] = IXGBE_READ_REG(hw, IXGBE_PCS1GANNP);
	regs_buff[1046] = IXGBE_READ_REG(hw, IXGBE_PCS1GANLPNP);
	regs_buff[1047] = IXGBE_READ_REG(hw, IXGBE_HLREG0);
	regs_buff[1048] = IXGBE_READ_REG(hw, IXGBE_HLREG1);
	regs_buff[1049] = IXGBE_READ_REG(hw, IXGBE_PAP);
	regs_buff[1050] = IXGBE_READ_REG(hw, IXGBE_MACA);
	regs_buff[1051] = IXGBE_READ_REG(hw, IXGBE_APAE);
	regs_buff[1052] = IXGBE_READ_REG(hw, IXGBE_ARD);
	regs_buff[1053] = IXGBE_READ_REG(hw, IXGBE_AIS);
	regs_buff[1054] = IXGBE_READ_REG(hw, IXGBE_MSCA);
	regs_buff[1055] = IXGBE_READ_REG(hw, IXGBE_MSRWD);
	regs_buff[1056] = IXGBE_READ_REG(hw, IXGBE_MLADD);
	regs_buff[1057] = IXGBE_READ_REG(hw, IXGBE_MHADD);
	regs_buff[1058] = IXGBE_READ_REG(hw, IXGBE_TREG);
	regs_buff[1059] = IXGBE_READ_REG(hw, IXGBE_PCSS1);
	regs_buff[1060] = IXGBE_READ_REG(hw, IXGBE_PCSS2);
	regs_buff[1061] = IXGBE_READ_REG(hw, IXGBE_XPCSS);
	regs_buff[1062] = IXGBE_READ_REG(hw, IXGBE_SERDESC);
	regs_buff[1063] = IXGBE_READ_REG(hw, IXGBE_MACS);
	regs_buff[1064] = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	regs_buff[1065] = IXGBE_READ_REG(hw, IXGBE_LINKS);
	regs_buff[1066] = IXGBE_READ_REG(hw, IXGBE_AUTOC2);
	regs_buff[1067] = IXGBE_READ_REG(hw, IXGBE_AUTOC3);
	regs_buff[1068] = IXGBE_READ_REG(hw, IXGBE_ANLP1);
	regs_buff[1069] = IXGBE_READ_REG(hw, IXGBE_ANLP2);
	regs_buff[1070] = IXGBE_READ_REG(hw, IXGBE_ATLASCTL);

	/* Diagnostic */
	regs_buff[1071] = IXGBE_READ_REG(hw, IXGBE_RDSTATCTL);
	for (i = 0; i < 8; i++)
		regs_buff[1072 + i] = IXGBE_READ_REG(hw, IXGBE_RDSTAT(i));
	regs_buff[1080] = IXGBE_READ_REG(hw, IXGBE_RDHMPN);
	for (i = 0; i < 4; i++)
		regs_buff[1081 + i] = IXGBE_READ_REG(hw, IXGBE_RIC_DW(i));
	regs_buff[1085] = IXGBE_READ_REG(hw, IXGBE_RDPROBE);
	regs_buff[1086] = IXGBE_READ_REG(hw, IXGBE_TDSTATCTL);
	for (i = 0; i < 8; i++)
		regs_buff[1087 + i] = IXGBE_READ_REG(hw, IXGBE_TDSTAT(i));
	regs_buff[1095] = IXGBE_READ_REG(hw, IXGBE_TDHMPN);
	for (i = 0; i < 4; i++)
		regs_buff[1096 + i] = IXGBE_READ_REG(hw, IXGBE_TIC_DW(i));
	regs_buff[1100] = IXGBE_READ_REG(hw, IXGBE_TDPROBE);
	regs_buff[1101] = IXGBE_READ_REG(hw, IXGBE_TXBUFCTRL);
	for (i = 0; i < 4; i++)
		regs_buff[1102 + i] = IXGBE_READ_REG(hw, IXGBE_TXBUFDATA(i));
	regs_buff[1106] = IXGBE_READ_REG(hw, IXGBE_RXBUFCTRL);
	for (i = 0; i < 4; i++)
		regs_buff[1107 + i] = IXGBE_READ_REG(hw, IXGBE_RXBUFDATA(i));
	for (i = 0; i < 8; i++)
		regs_buff[1111 + i] = IXGBE_READ_REG(hw, IXGBE_PCIE_DIAG(i));
	regs_buff[1119] = IXGBE_READ_REG(hw, IXGBE_RFVAL);
	regs_buff[1120] = IXGBE_READ_REG(hw, IXGBE_MDFTC1);
	regs_buff[1121] = IXGBE_READ_REG(hw, IXGBE_MDFTC2);
	regs_buff[1122] = IXGBE_READ_REG(hw, IXGBE_MDFTFIFO1);
	regs_buff[1123] = IXGBE_READ_REG(hw, IXGBE_MDFTFIFO2);
	regs_buff[1124] = IXGBE_READ_REG(hw, IXGBE_MDFTS);
	regs_buff[1125] = IXGBE_READ_REG(hw, IXGBE_PCIEECCCTL);
	regs_buff[1126] = IXGBE_READ_REG(hw, IXGBE_PBTXECC);
	regs_buff[1127] = IXGBE_READ_REG(hw, IXGBE_PBRXECC);

	/* 82599 X540 specific registers  */
	regs_buff[1128] = IXGBE_READ_REG(hw, IXGBE_MFLCN);

	/* 82599 X540 specific DCB registers  */
	regs_buff[1129] = IXGBE_READ_REG(hw, IXGBE_RTRUP2TC);
	regs_buff[1130] = IXGBE_READ_REG(hw, IXGBE_RTTUP2TC);
	for (i = 0; i < 4; i++)
		regs_buff[1131 + i] = IXGBE_READ_REG(hw, IXGBE_TXLLQ(i));
	regs_buff[1135] = IXGBE_READ_REG(hw, IXGBE_RTTBCNRM);
					/* same as RTTQCNRM */
	regs_buff[1136] = IXGBE_READ_REG(hw, IXGBE_RTTBCNRD);
					/* same as RTTQCNRR */

	/* X540 specific DCB registers  */
	regs_buff[1137] = IXGBE_READ_REG(hw, IXGBE_RTTQCNCR);
	regs_buff[1138] = IXGBE_READ_REG(hw, IXGBE_RTTQCNTG);

	/* Security config registers */
	regs_buff[1139] = IXGBE_READ_REG(hw, IXGBE_SECTXCTRL);
	regs_buff[1140] = IXGBE_READ_REG(hw, IXGBE_SECTXSTAT);
	regs_buff[1141] = IXGBE_READ_REG(hw, IXGBE_SECTXBUFFAF);
	regs_buff[1142] = IXGBE_READ_REG(hw, IXGBE_SECTXMINIFG);
	regs_buff[1143] = IXGBE_READ_REG(hw, IXGBE_SECRXCTRL);
	regs_buff[1144] = IXGBE_READ_REG(hw, IXGBE_SECRXSTAT);
}