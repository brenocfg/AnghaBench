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
typedef  int u64 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct TYPE_4__ {int multicast; int rx_errors; int rx_crc_errors; int rx_fifo_errors; int rx_missed_errors; int rx_over_errors; scalar_t__ tx_window_errors; scalar_t__ tx_heartbeat_errors; scalar_t__ tx_fifo_errors; scalar_t__ tx_carrier_errors; scalar_t__ tx_aborted_errors; scalar_t__ rx_frame_errors; scalar_t__ tx_errors; scalar_t__ collisions; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct net_device {int flags; TYPE_2__ stats; } ;
struct TYPE_3__ {int mprcl; int mprch; int bprcl; int ruc; int roc; int crcerrs; int icbc; int ecbc; int mpc; int /*<<< orphan*/  gotcl; int /*<<< orphan*/  gorcl; int /*<<< orphan*/  gptcl; int /*<<< orphan*/  gprcl; int /*<<< orphan*/  rjc; int /*<<< orphan*/  xofftxc; int /*<<< orphan*/  xoffrxc; int /*<<< orphan*/  xontxc; int /*<<< orphan*/  xonrxc; int /*<<< orphan*/  mcftc; int /*<<< orphan*/  mcfrc; int /*<<< orphan*/  pftc; int /*<<< orphan*/  pfrc; int /*<<< orphan*/  lfc; int /*<<< orphan*/  rfc; int /*<<< orphan*/  ibic; int /*<<< orphan*/  tsctfc; int /*<<< orphan*/  tsctc; int /*<<< orphan*/  plt64c; int /*<<< orphan*/  dc; int /*<<< orphan*/  toth; int /*<<< orphan*/  totl; int /*<<< orphan*/  gotch; int /*<<< orphan*/  jptch; int /*<<< orphan*/  jptcl; int /*<<< orphan*/  vptch; int /*<<< orphan*/  vptcl; int /*<<< orphan*/  uptch; int /*<<< orphan*/  uptcl; int /*<<< orphan*/  mptch; int /*<<< orphan*/  mptcl; int /*<<< orphan*/  bptch; int /*<<< orphan*/  bptcl; int /*<<< orphan*/  gptch; int /*<<< orphan*/  tpth; int /*<<< orphan*/  tptl; int /*<<< orphan*/  rlec; int /*<<< orphan*/  rnbc; int /*<<< orphan*/  torh; int /*<<< orphan*/  torl; int /*<<< orphan*/  gorch; int /*<<< orphan*/  jprch; int /*<<< orphan*/  jprcl; int /*<<< orphan*/  vprch; int /*<<< orphan*/  vprcl; int /*<<< orphan*/  uprch; int /*<<< orphan*/  uprcl; int /*<<< orphan*/  gprch; int /*<<< orphan*/  tprh; int /*<<< orphan*/  tprl; int /*<<< orphan*/  bprch; } ;
struct ixgb_adapter {TYPE_1__ stats; int /*<<< orphan*/  hw; struct pci_dev* pdev; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPRCH ; 
 int /*<<< orphan*/  BPRCL ; 
 int /*<<< orphan*/  BPTCH ; 
 int /*<<< orphan*/  BPTCL ; 
 int /*<<< orphan*/  CRCERRS ; 
 int /*<<< orphan*/  DC ; 
 int /*<<< orphan*/  ECBC ; 
 int /*<<< orphan*/  GORCH ; 
 int /*<<< orphan*/  GORCL ; 
 int /*<<< orphan*/  GOTCH ; 
 int /*<<< orphan*/  GOTCL ; 
 int /*<<< orphan*/  GPRCH ; 
 int /*<<< orphan*/  GPRCL ; 
 int /*<<< orphan*/  GPTCH ; 
 int /*<<< orphan*/  GPTCL ; 
 int /*<<< orphan*/  IBIC ; 
 int /*<<< orphan*/  ICBC ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 scalar_t__ IXGB_MAX_NUM_MULTICAST_ADDRESSES ; 
 int IXGB_READ_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JPRCH ; 
 int /*<<< orphan*/  JPRCL ; 
 int /*<<< orphan*/  JPTCH ; 
 int /*<<< orphan*/  JPTCL ; 
 int /*<<< orphan*/  LFC ; 
 int /*<<< orphan*/  MCFRC ; 
 int /*<<< orphan*/  MCFTC ; 
 int /*<<< orphan*/  MPC ; 
 int /*<<< orphan*/  MPRCH ; 
 int /*<<< orphan*/  MPRCL ; 
 int /*<<< orphan*/  MPTCH ; 
 int /*<<< orphan*/  MPTCL ; 
 int /*<<< orphan*/  PFRC ; 
 int /*<<< orphan*/  PFTC ; 
 int /*<<< orphan*/  PLT64C ; 
 int /*<<< orphan*/  RFC ; 
 int /*<<< orphan*/  RJC ; 
 int /*<<< orphan*/  RLEC ; 
 int /*<<< orphan*/  RNBC ; 
 int /*<<< orphan*/  ROC ; 
 int /*<<< orphan*/  RUC ; 
 int /*<<< orphan*/  TORH ; 
 int /*<<< orphan*/  TORL ; 
 int /*<<< orphan*/  TOTH ; 
 int /*<<< orphan*/  TOTL ; 
 int /*<<< orphan*/  TPRH ; 
 int /*<<< orphan*/  TPRL ; 
 int /*<<< orphan*/  TPTH ; 
 int /*<<< orphan*/  TPTL ; 
 int /*<<< orphan*/  TSCTC ; 
 int /*<<< orphan*/  TSCTFC ; 
 int /*<<< orphan*/  UPRCH ; 
 int /*<<< orphan*/  UPRCL ; 
 int /*<<< orphan*/  UPTCH ; 
 int /*<<< orphan*/  UPTCL ; 
 int /*<<< orphan*/  VPRCH ; 
 int /*<<< orphan*/  VPRCL ; 
 int /*<<< orphan*/  VPTCH ; 
 int /*<<< orphan*/  VPTCL ; 
 int /*<<< orphan*/  XOFFRXC ; 
 int /*<<< orphan*/  XOFFTXC ; 
 int /*<<< orphan*/  XONRXC ; 
 int /*<<< orphan*/  XONTXC ; 
 scalar_t__ netdev_mc_count (struct net_device*) ; 
 scalar_t__ pci_channel_offline (struct pci_dev*) ; 

void
ixgb_update_stats(struct ixgb_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;

	/* Prevent stats update while adapter is being reset */
	if (pci_channel_offline(pdev))
		return;

	if ((netdev->flags & IFF_PROMISC) || (netdev->flags & IFF_ALLMULTI) ||
	   (netdev_mc_count(netdev) > IXGB_MAX_NUM_MULTICAST_ADDRESSES)) {
		u64 multi = IXGB_READ_REG(&adapter->hw, MPRCL);
		u32 bcast_l = IXGB_READ_REG(&adapter->hw, BPRCL);
		u32 bcast_h = IXGB_READ_REG(&adapter->hw, BPRCH);
		u64 bcast = ((u64)bcast_h << 32) | bcast_l;

		multi |= ((u64)IXGB_READ_REG(&adapter->hw, MPRCH) << 32);
		/* fix up multicast stats by removing broadcasts */
		if (multi >= bcast)
			multi -= bcast;

		adapter->stats.mprcl += (multi & 0xFFFFFFFF);
		adapter->stats.mprch += (multi >> 32);
		adapter->stats.bprcl += bcast_l;
		adapter->stats.bprch += bcast_h;
	} else {
		adapter->stats.mprcl += IXGB_READ_REG(&adapter->hw, MPRCL);
		adapter->stats.mprch += IXGB_READ_REG(&adapter->hw, MPRCH);
		adapter->stats.bprcl += IXGB_READ_REG(&adapter->hw, BPRCL);
		adapter->stats.bprch += IXGB_READ_REG(&adapter->hw, BPRCH);
	}
	adapter->stats.tprl += IXGB_READ_REG(&adapter->hw, TPRL);
	adapter->stats.tprh += IXGB_READ_REG(&adapter->hw, TPRH);
	adapter->stats.gprcl += IXGB_READ_REG(&adapter->hw, GPRCL);
	adapter->stats.gprch += IXGB_READ_REG(&adapter->hw, GPRCH);
	adapter->stats.uprcl += IXGB_READ_REG(&adapter->hw, UPRCL);
	adapter->stats.uprch += IXGB_READ_REG(&adapter->hw, UPRCH);
	adapter->stats.vprcl += IXGB_READ_REG(&adapter->hw, VPRCL);
	adapter->stats.vprch += IXGB_READ_REG(&adapter->hw, VPRCH);
	adapter->stats.jprcl += IXGB_READ_REG(&adapter->hw, JPRCL);
	adapter->stats.jprch += IXGB_READ_REG(&adapter->hw, JPRCH);
	adapter->stats.gorcl += IXGB_READ_REG(&adapter->hw, GORCL);
	adapter->stats.gorch += IXGB_READ_REG(&adapter->hw, GORCH);
	adapter->stats.torl += IXGB_READ_REG(&adapter->hw, TORL);
	adapter->stats.torh += IXGB_READ_REG(&adapter->hw, TORH);
	adapter->stats.rnbc += IXGB_READ_REG(&adapter->hw, RNBC);
	adapter->stats.ruc += IXGB_READ_REG(&adapter->hw, RUC);
	adapter->stats.roc += IXGB_READ_REG(&adapter->hw, ROC);
	adapter->stats.rlec += IXGB_READ_REG(&adapter->hw, RLEC);
	adapter->stats.crcerrs += IXGB_READ_REG(&adapter->hw, CRCERRS);
	adapter->stats.icbc += IXGB_READ_REG(&adapter->hw, ICBC);
	adapter->stats.ecbc += IXGB_READ_REG(&adapter->hw, ECBC);
	adapter->stats.mpc += IXGB_READ_REG(&adapter->hw, MPC);
	adapter->stats.tptl += IXGB_READ_REG(&adapter->hw, TPTL);
	adapter->stats.tpth += IXGB_READ_REG(&adapter->hw, TPTH);
	adapter->stats.gptcl += IXGB_READ_REG(&adapter->hw, GPTCL);
	adapter->stats.gptch += IXGB_READ_REG(&adapter->hw, GPTCH);
	adapter->stats.bptcl += IXGB_READ_REG(&adapter->hw, BPTCL);
	adapter->stats.bptch += IXGB_READ_REG(&adapter->hw, BPTCH);
	adapter->stats.mptcl += IXGB_READ_REG(&adapter->hw, MPTCL);
	adapter->stats.mptch += IXGB_READ_REG(&adapter->hw, MPTCH);
	adapter->stats.uptcl += IXGB_READ_REG(&adapter->hw, UPTCL);
	adapter->stats.uptch += IXGB_READ_REG(&adapter->hw, UPTCH);
	adapter->stats.vptcl += IXGB_READ_REG(&adapter->hw, VPTCL);
	adapter->stats.vptch += IXGB_READ_REG(&adapter->hw, VPTCH);
	adapter->stats.jptcl += IXGB_READ_REG(&adapter->hw, JPTCL);
	adapter->stats.jptch += IXGB_READ_REG(&adapter->hw, JPTCH);
	adapter->stats.gotcl += IXGB_READ_REG(&adapter->hw, GOTCL);
	adapter->stats.gotch += IXGB_READ_REG(&adapter->hw, GOTCH);
	adapter->stats.totl += IXGB_READ_REG(&adapter->hw, TOTL);
	adapter->stats.toth += IXGB_READ_REG(&adapter->hw, TOTH);
	adapter->stats.dc += IXGB_READ_REG(&adapter->hw, DC);
	adapter->stats.plt64c += IXGB_READ_REG(&adapter->hw, PLT64C);
	adapter->stats.tsctc += IXGB_READ_REG(&adapter->hw, TSCTC);
	adapter->stats.tsctfc += IXGB_READ_REG(&adapter->hw, TSCTFC);
	adapter->stats.ibic += IXGB_READ_REG(&adapter->hw, IBIC);
	adapter->stats.rfc += IXGB_READ_REG(&adapter->hw, RFC);
	adapter->stats.lfc += IXGB_READ_REG(&adapter->hw, LFC);
	adapter->stats.pfrc += IXGB_READ_REG(&adapter->hw, PFRC);
	adapter->stats.pftc += IXGB_READ_REG(&adapter->hw, PFTC);
	adapter->stats.mcfrc += IXGB_READ_REG(&adapter->hw, MCFRC);
	adapter->stats.mcftc += IXGB_READ_REG(&adapter->hw, MCFTC);
	adapter->stats.xonrxc += IXGB_READ_REG(&adapter->hw, XONRXC);
	adapter->stats.xontxc += IXGB_READ_REG(&adapter->hw, XONTXC);
	adapter->stats.xoffrxc += IXGB_READ_REG(&adapter->hw, XOFFRXC);
	adapter->stats.xofftxc += IXGB_READ_REG(&adapter->hw, XOFFTXC);
	adapter->stats.rjc += IXGB_READ_REG(&adapter->hw, RJC);

	/* Fill out the OS statistics structure */

	netdev->stats.rx_packets = adapter->stats.gprcl;
	netdev->stats.tx_packets = adapter->stats.gptcl;
	netdev->stats.rx_bytes = adapter->stats.gorcl;
	netdev->stats.tx_bytes = adapter->stats.gotcl;
	netdev->stats.multicast = adapter->stats.mprcl;
	netdev->stats.collisions = 0;

	/* ignore RLEC as it reports errors for padded (<64bytes) frames
	 * with a length in the type/len field */
	netdev->stats.rx_errors =
	    /* adapter->stats.rnbc + */ adapter->stats.crcerrs +
	    adapter->stats.ruc +
	    adapter->stats.roc /*+ adapter->stats.rlec */  +
	    adapter->stats.icbc +
	    adapter->stats.ecbc + adapter->stats.mpc;

	/* see above
	 * netdev->stats.rx_length_errors = adapter->stats.rlec;
	 */

	netdev->stats.rx_crc_errors = adapter->stats.crcerrs;
	netdev->stats.rx_fifo_errors = adapter->stats.mpc;
	netdev->stats.rx_missed_errors = adapter->stats.mpc;
	netdev->stats.rx_over_errors = adapter->stats.mpc;

	netdev->stats.tx_errors = 0;
	netdev->stats.rx_frame_errors = 0;
	netdev->stats.tx_aborted_errors = 0;
	netdev->stats.tx_carrier_errors = 0;
	netdev->stats.tx_fifo_errors = 0;
	netdev->stats.tx_heartbeat_errors = 0;
	netdev->stats.tx_window_errors = 0;
}