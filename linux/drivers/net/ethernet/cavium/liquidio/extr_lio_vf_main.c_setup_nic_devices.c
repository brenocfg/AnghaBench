#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_16__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {scalar_t__ base_queue; int /*<<< orphan*/  num_oqueues; int /*<<< orphan*/  num_iqueues; } ;
union oct_nic_if_cfg {scalar_t__ u64; TYPE_2__ s; } ;
typedef  size_t u8 ;
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct octeon_soft_command {int /*<<< orphan*/  caller_is_done; int /*<<< orphan*/  sc_status; int /*<<< orphan*/  complete; scalar_t__ iq_no; scalar_t__ virtdptr; scalar_t__ virtrptr; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* enable_interrupt ) (struct octeon_device*,int /*<<< orphan*/ ) ;} ;
struct TYPE_26__ {int /*<<< orphan*/  liquidio_firmware_version; } ;
struct TYPE_24__ {int /*<<< orphan*/  rings_per_vf; } ;
struct octeon_device {int pf_num; size_t ifcount; scalar_t__ chip_id; int priv_flags; int no_speed_setting; TYPE_16__* pci_dev; TYPE_10__ fn_list; struct octdev_props* props; TYPE_3__ fw_info; TYPE_1__ sriov_info; } ;
struct octdev_props {struct net_device* netdev; int /*<<< orphan*/  gmxport; } ;
struct net_device {int hw_enc_features; int vlan_features; int features; int hw_features; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_30__ {int /*<<< orphan*/  u64; } ;
struct TYPE_31__ {int /*<<< orphan*/  macaddr_spoofchk; int /*<<< orphan*/  macaddr_is_admin_asgnd; TYPE_7__ link; int /*<<< orphan*/  gmxport; scalar_t__ hw_addr; TYPE_5__* txpciq; TYPE_4__* rxpciq; } ;
struct TYPE_32__ {char* liquidio_firmware_version; TYPE_8__ linfo; int /*<<< orphan*/  oqmask; int /*<<< orphan*/  iqmask; } ;
struct liquidio_if_cfg_resp {int status; TYPE_9__ cfg_info; } ;
struct liquidio_if_cfg_info {int dummy; } ;
struct lio_version {void* micro; void* minor; void* major; } ;
struct TYPE_29__ {int /*<<< orphan*/  u64; } ;
struct TYPE_22__ {int num_rxpciq; int num_txpciq; TYPE_14__* rxpciq; TYPE_12__* txpciq; scalar_t__ hw_addr; int /*<<< orphan*/  gmxport; int /*<<< orphan*/  macaddr_spoofchk; int /*<<< orphan*/  macaddr_is_admin_asgnd; TYPE_6__ link; } ;
struct lio {int ifidx; int dev_capability; int enc_dev_capability; int /*<<< orphan*/  link_changes; struct octeon_device* oct_dev; int /*<<< orphan*/  rxq; int /*<<< orphan*/  rx_qsize; int /*<<< orphan*/  txq; int /*<<< orphan*/  tx_qsize; TYPE_15__ linfo; struct net_device* netdev; struct octdev_props* octprops; int /*<<< orphan*/  msg_enable; } ;
struct TYPE_28__ {int /*<<< orphan*/  u64; } ;
struct TYPE_27__ {int /*<<< orphan*/  u64; } ;
struct TYPE_23__ {int /*<<< orphan*/  dev; } ;
struct TYPE_20__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_21__ {TYPE_13__ s; int /*<<< orphan*/  u64; } ;
struct TYPE_18__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_19__ {TYPE_11__ s; int /*<<< orphan*/  u64; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVM_CAST64 (scalar_t__) ; 
 int /*<<< orphan*/  DEFAULT_MSG_ENABLE ; 
 int EIO ; 
 int ENODEV ; 
 int ETH_ALEN ; 
 struct lio* GET_LIO (struct net_device*) ; 
 int IQ_SEND_FAILED ; 
 int /*<<< orphan*/  LIO_IFSTATE_DROQ_OPS ; 
 int /*<<< orphan*/  LIO_IFSTATE_REGISTERED ; 
 int /*<<< orphan*/  LIO_MAX_MTU_SIZE ; 
 int /*<<< orphan*/  LIO_MIN_MTU_SIZE ; 
 int /*<<< orphan*/  LIO_SIZE ; 
 int /*<<< orphan*/  LIQUIDIO_BASE_MAJOR_VERSION ; 
 int /*<<< orphan*/  LIQUIDIO_BASE_MICRO_VERSION ; 
 int /*<<< orphan*/  LIQUIDIO_BASE_MINOR_VERSION ; 
 int NETIF_F_GRO ; 
 int NETIF_F_GSO_UDP_TUNNEL ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_LRO ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int /*<<< orphan*/  OCTEON_ALL_INTR ; 
 scalar_t__ OCTEON_CN23XX_VF_VID ; 
 int /*<<< orphan*/  OCTEON_REQUEST_PENDING ; 
 int /*<<< orphan*/  OCTNET_CMD_LRO_ENABLE ; 
 int /*<<< orphan*/  OCTNET_CMD_RXCSUM_ENABLE ; 
 int /*<<< orphan*/  OCTNET_CMD_TNL_RX_CSUM_CTL ; 
 int /*<<< orphan*/  OCTNET_CMD_TNL_TX_CSUM_CTL ; 
 int OCTNET_CMD_TXCSUM_ENABLE ; 
 int /*<<< orphan*/  OCTNIC_GSO_MAX_SIZE ; 
 int OCTNIC_LROIPV4 ; 
 int OCTNIC_LROIPV6 ; 
 int OCT_PRIV_FLAG_DEFAULT ; 
 int /*<<< orphan*/  OPCODE_NIC ; 
 int /*<<< orphan*/  OPCODE_NIC_IF_CFG ; 
 int /*<<< orphan*/  OPCODE_NIC_INFO ; 
 int /*<<< orphan*/  REQTYPE_NORESP_NET ; 
 int /*<<< orphan*/  REQTYPE_NORESP_NET_SG ; 
 int /*<<< orphan*/  REQTYPE_RESP_NET_SG ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 struct net_device* alloc_etherdev_mq (int /*<<< orphan*/ ,int) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,size_t,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  free_netbuf ; 
 int /*<<< orphan*/  free_netsgbuf ; 
 int /*<<< orphan*/  free_netsgbuf_with_resp ; 
 int hweight64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifstate_set (struct lio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lio_nic_info ; 
 scalar_t__ lio_setup_glists (struct octeon_device*,struct lio*,int) ; 
 int /*<<< orphan*/  lionetdevops ; 
 int /*<<< orphan*/  liquidio_destroy_nic_device (struct octeon_device*,size_t) ; 
 int /*<<< orphan*/  liquidio_set_ethtool_ops (struct net_device*) ; 
 int /*<<< orphan*/  liquidio_set_feature (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  liquidio_set_rxcsum_command (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ liquidio_setup_io_queues (struct octeon_device*,size_t,int,int) ; 
 int /*<<< orphan*/  memset (struct lio*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_set_gso_max_size (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ octeon_alloc_soft_command (struct octeon_device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_free_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  octeon_get_rx_qsize (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_get_tx_qsize (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_prepare_soft_command (struct octeon_device*,struct octeon_soft_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_register_dispatch_fn (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct octeon_device*) ; 
 int /*<<< orphan*/  octeon_register_reqtype_free_fn (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int octeon_send_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  octeon_swap_8B_data (scalar_t__*,int) ; 
 scalar_t__ register_netdev (struct net_device*) ; 
 scalar_t__ setup_link_status_change_wq (struct net_device*) ; 
 scalar_t__ setup_rx_oom_poll_fn (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int wait_for_sc_completion_timeout (struct octeon_device*,struct octeon_soft_command*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_nic_devices(struct octeon_device *octeon_dev)
{
	int retval, num_iqueues, num_oqueues;
	u32 resp_size, data_size;
	struct liquidio_if_cfg_resp *resp;
	struct octeon_soft_command *sc;
	union oct_nic_if_cfg if_cfg;
	struct octdev_props *props;
	struct net_device *netdev;
	struct lio_version *vdata;
	struct lio *lio = NULL;
	u8 mac[ETH_ALEN], i, j;
	u32 ifidx_or_pfnum;

	ifidx_or_pfnum = octeon_dev->pf_num;

	/* This is to handle link status changes */
	octeon_register_dispatch_fn(octeon_dev, OPCODE_NIC, OPCODE_NIC_INFO,
				    lio_nic_info, octeon_dev);

	/* REQTYPE_RESP_NET and REQTYPE_SOFT_COMMAND do not have free functions.
	 * They are handled directly.
	 */
	octeon_register_reqtype_free_fn(octeon_dev, REQTYPE_NORESP_NET,
					free_netbuf);

	octeon_register_reqtype_free_fn(octeon_dev, REQTYPE_NORESP_NET_SG,
					free_netsgbuf);

	octeon_register_reqtype_free_fn(octeon_dev, REQTYPE_RESP_NET_SG,
					free_netsgbuf_with_resp);

	for (i = 0; i < octeon_dev->ifcount; i++) {
		resp_size = sizeof(struct liquidio_if_cfg_resp);
		data_size = sizeof(struct lio_version);
		sc = (struct octeon_soft_command *)
			octeon_alloc_soft_command(octeon_dev, data_size,
						  resp_size, 0);
		resp = (struct liquidio_if_cfg_resp *)sc->virtrptr;
		vdata = (struct lio_version *)sc->virtdptr;

		*((u64 *)vdata) = 0;
		vdata->major = cpu_to_be16(LIQUIDIO_BASE_MAJOR_VERSION);
		vdata->minor = cpu_to_be16(LIQUIDIO_BASE_MINOR_VERSION);
		vdata->micro = cpu_to_be16(LIQUIDIO_BASE_MICRO_VERSION);

		if_cfg.u64 = 0;

		if_cfg.s.num_iqueues = octeon_dev->sriov_info.rings_per_vf;
		if_cfg.s.num_oqueues = octeon_dev->sriov_info.rings_per_vf;
		if_cfg.s.base_queue = 0;

		sc->iq_no = 0;

		octeon_prepare_soft_command(octeon_dev, sc, OPCODE_NIC,
					    OPCODE_NIC_IF_CFG, 0, if_cfg.u64,
					    0);

		init_completion(&sc->complete);
		sc->sc_status = OCTEON_REQUEST_PENDING;

		retval = octeon_send_soft_command(octeon_dev, sc);
		if (retval == IQ_SEND_FAILED) {
			dev_err(&octeon_dev->pci_dev->dev,
				"iq/oq config failed status: %x\n", retval);
			/* Soft instr is freed by driver in case of failure. */
			octeon_free_soft_command(octeon_dev, sc);
			return(-EIO);
		}

		/* Sleep on a wait queue till the cond flag indicates that the
		 * response arrived or timed-out.
		 */
		retval = wait_for_sc_completion_timeout(octeon_dev, sc, 0);
		if (retval)
			return retval;

		retval = resp->status;
		if (retval) {
			dev_err(&octeon_dev->pci_dev->dev,
				"iq/oq config failed, retval = %d\n", retval);
			WRITE_ONCE(sc->caller_is_done, true);
			return -EIO;
		}

		snprintf(octeon_dev->fw_info.liquidio_firmware_version,
			 32, "%s",
			 resp->cfg_info.liquidio_firmware_version);

		octeon_swap_8B_data((u64 *)(&resp->cfg_info),
				    (sizeof(struct liquidio_if_cfg_info)) >> 3);

		num_iqueues = hweight64(resp->cfg_info.iqmask);
		num_oqueues = hweight64(resp->cfg_info.oqmask);

		if (!(num_iqueues) || !(num_oqueues)) {
			dev_err(&octeon_dev->pci_dev->dev,
				"Got bad iqueues (%016llx) or oqueues (%016llx) from firmware.\n",
				resp->cfg_info.iqmask, resp->cfg_info.oqmask);
			WRITE_ONCE(sc->caller_is_done, true);
			goto setup_nic_dev_done;
		}
		dev_dbg(&octeon_dev->pci_dev->dev,
			"interface %d, iqmask %016llx, oqmask %016llx, numiqueues %d, numoqueues %d\n",
			i, resp->cfg_info.iqmask, resp->cfg_info.oqmask,
			num_iqueues, num_oqueues);

		netdev = alloc_etherdev_mq(LIO_SIZE, num_iqueues);

		if (!netdev) {
			dev_err(&octeon_dev->pci_dev->dev, "Device allocation failed\n");
			WRITE_ONCE(sc->caller_is_done, true);
			goto setup_nic_dev_done;
		}

		SET_NETDEV_DEV(netdev, &octeon_dev->pci_dev->dev);

		/* Associate the routines that will handle different
		 * netdev tasks.
		 */
		netdev->netdev_ops = &lionetdevops;

		lio = GET_LIO(netdev);

		memset(lio, 0, sizeof(struct lio));

		lio->ifidx = ifidx_or_pfnum;

		props = &octeon_dev->props[i];
		props->gmxport = resp->cfg_info.linfo.gmxport;
		props->netdev = netdev;

		lio->linfo.num_rxpciq = num_oqueues;
		lio->linfo.num_txpciq = num_iqueues;

		for (j = 0; j < num_oqueues; j++) {
			lio->linfo.rxpciq[j].u64 =
			    resp->cfg_info.linfo.rxpciq[j].u64;
		}
		for (j = 0; j < num_iqueues; j++) {
			lio->linfo.txpciq[j].u64 =
			    resp->cfg_info.linfo.txpciq[j].u64;
		}

		lio->linfo.hw_addr = resp->cfg_info.linfo.hw_addr;
		lio->linfo.gmxport = resp->cfg_info.linfo.gmxport;
		lio->linfo.link.u64 = resp->cfg_info.linfo.link.u64;
		lio->linfo.macaddr_is_admin_asgnd =
			resp->cfg_info.linfo.macaddr_is_admin_asgnd;
		lio->linfo.macaddr_spoofchk =
			resp->cfg_info.linfo.macaddr_spoofchk;

		lio->msg_enable = netif_msg_init(debug, DEFAULT_MSG_ENABLE);

		lio->dev_capability = NETIF_F_HIGHDMA
				      | NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM
				      | NETIF_F_SG | NETIF_F_RXCSUM
				      | NETIF_F_TSO | NETIF_F_TSO6
				      | NETIF_F_GRO
				      | NETIF_F_LRO;
		netif_set_gso_max_size(netdev, OCTNIC_GSO_MAX_SIZE);

		/* Copy of transmit encapsulation capabilities:
		 * TSO, TSO6, Checksums for this device
		 */
		lio->enc_dev_capability = NETIF_F_IP_CSUM
					  | NETIF_F_IPV6_CSUM
					  | NETIF_F_GSO_UDP_TUNNEL
					  | NETIF_F_HW_CSUM | NETIF_F_SG
					  | NETIF_F_RXCSUM
					  | NETIF_F_TSO | NETIF_F_TSO6
					  | NETIF_F_LRO;

		netdev->hw_enc_features =
		    (lio->enc_dev_capability & ~NETIF_F_LRO);
		netdev->vlan_features = lio->dev_capability;
		/* Add any unchangeable hw features */
		lio->dev_capability |= NETIF_F_HW_VLAN_CTAG_FILTER |
				       NETIF_F_HW_VLAN_CTAG_RX |
				       NETIF_F_HW_VLAN_CTAG_TX;

		netdev->features = (lio->dev_capability & ~NETIF_F_LRO);

		netdev->hw_features = lio->dev_capability;
		netdev->hw_features &= ~NETIF_F_HW_VLAN_CTAG_RX;

		/* MTU range: 68 - 16000 */
		netdev->min_mtu = LIO_MIN_MTU_SIZE;
		netdev->max_mtu = LIO_MAX_MTU_SIZE;

		WRITE_ONCE(sc->caller_is_done, true);

		/* Point to the  properties for octeon device to which this
		 * interface belongs.
		 */
		lio->oct_dev = octeon_dev;
		lio->octprops = props;
		lio->netdev = netdev;

		dev_dbg(&octeon_dev->pci_dev->dev,
			"if%d gmx: %d hw_addr: 0x%llx\n", i,
			lio->linfo.gmxport, CVM_CAST64(lio->linfo.hw_addr));

		/* 64-bit swap required on LE machines */
		octeon_swap_8B_data(&lio->linfo.hw_addr, 1);
		for (j = 0; j < ETH_ALEN; j++)
			mac[j] = *((u8 *)(((u8 *)&lio->linfo.hw_addr) + 2 + j));

		/* Copy MAC Address to OS network device structure */
		ether_addr_copy(netdev->dev_addr, mac);

		if (liquidio_setup_io_queues(octeon_dev, i,
					     lio->linfo.num_txpciq,
					     lio->linfo.num_rxpciq)) {
			dev_err(&octeon_dev->pci_dev->dev, "I/O queues creation failed\n");
			goto setup_nic_dev_free;
		}

		ifstate_set(lio, LIO_IFSTATE_DROQ_OPS);

		/* For VFs, enable Octeon device interrupts here,
		 * as this is contingent upon IO queue setup
		 */
		octeon_dev->fn_list.enable_interrupt(octeon_dev,
						     OCTEON_ALL_INTR);

		/* By default all interfaces on a single Octeon uses the same
		 * tx and rx queues
		 */
		lio->txq = lio->linfo.txpciq[0].s.q_no;
		lio->rxq = lio->linfo.rxpciq[0].s.q_no;

		lio->tx_qsize = octeon_get_tx_qsize(octeon_dev, lio->txq);
		lio->rx_qsize = octeon_get_rx_qsize(octeon_dev, lio->rxq);

		if (lio_setup_glists(octeon_dev, lio, num_iqueues)) {
			dev_err(&octeon_dev->pci_dev->dev,
				"Gather list allocation failed\n");
			goto setup_nic_dev_free;
		}

		/* Register ethtool support */
		liquidio_set_ethtool_ops(netdev);
		if (lio->oct_dev->chip_id == OCTEON_CN23XX_VF_VID)
			octeon_dev->priv_flags = OCT_PRIV_FLAG_DEFAULT;
		else
			octeon_dev->priv_flags = 0x0;

		if (netdev->features & NETIF_F_LRO)
			liquidio_set_feature(netdev, OCTNET_CMD_LRO_ENABLE,
					     OCTNIC_LROIPV4 | OCTNIC_LROIPV6);

		if (setup_link_status_change_wq(netdev))
			goto setup_nic_dev_free;

		if (setup_rx_oom_poll_fn(netdev))
			goto setup_nic_dev_free;

		/* Register the network device with the OS */
		if (register_netdev(netdev)) {
			dev_err(&octeon_dev->pci_dev->dev, "Device registration failed\n");
			goto setup_nic_dev_free;
		}

		dev_dbg(&octeon_dev->pci_dev->dev,
			"Setup NIC ifidx:%d mac:%02x%02x%02x%02x%02x%02x\n",
			i, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
		netif_carrier_off(netdev);
		lio->link_changes++;

		ifstate_set(lio, LIO_IFSTATE_REGISTERED);

		/* Sending command to firmware to enable Rx checksum offload
		 * by default at the time of setup of Liquidio driver for
		 * this device
		 */
		liquidio_set_rxcsum_command(netdev, OCTNET_CMD_TNL_RX_CSUM_CTL,
					    OCTNET_CMD_RXCSUM_ENABLE);
		liquidio_set_feature(netdev, OCTNET_CMD_TNL_TX_CSUM_CTL,
				     OCTNET_CMD_TXCSUM_ENABLE);

		dev_dbg(&octeon_dev->pci_dev->dev,
			"NIC ifidx:%d Setup successful\n", i);

		octeon_dev->no_speed_setting = 1;
	}

	return 0;

setup_nic_dev_free:

	while (i--) {
		dev_err(&octeon_dev->pci_dev->dev,
			"NIC ifidx:%d Setup failed\n", i);
		liquidio_destroy_nic_device(octeon_dev, i);
	}

setup_nic_dev_done:

	return -ENODEV;
}