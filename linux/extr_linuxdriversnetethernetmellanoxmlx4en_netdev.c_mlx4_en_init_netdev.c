#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dev_port; int hw_features; int vlan_features; int features; int gso_partial_features; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  addr_assign_type; int /*<<< orphan*/  addr_len; } ;
struct mlx4_en_tx_ring {int dummy; } ;
struct mlx4_en_rx_desc {int dummy; } ;
struct TYPE_22__ {int /*<<< orphan*/  rx_filter; int /*<<< orphan*/  tx_type; scalar_t__ flags; } ;
struct mlx4_en_priv {int port; int port_up; int cqe_factor; int cqe_size; int mac_index; int allocated; int registered; int /*<<< orphan*/  stats_bitmap; int /*<<< orphan*/  service_task; int /*<<< orphan*/  stats_task; scalar_t__ rx_skb_size; struct net_device* dev; int /*<<< orphan*/  max_mtu; void* rss_hash_fn; int /*<<< orphan*/  pflags; int /*<<< orphan*/  rx_ring_num; int /*<<< orphan*/ * tx_ring_num; struct mlx4_en_dev* mdev; int /*<<< orphan*/  res; TYPE_4__ hwtstamp_config; int /*<<< orphan*/  stride; int /*<<< orphan*/  current_mac; int /*<<< orphan*/  flags; int /*<<< orphan*/ * mac_hash; int /*<<< orphan*/  msg_enable; void** tx_cq; void** tx_ring; int /*<<< orphan*/  rss_key; int /*<<< orphan*/  tx_work_limit; int /*<<< orphan*/  num_tx_rings_p_up; int /*<<< orphan*/  ctrl_flags; struct mlx4_en_port_profile* prof; int /*<<< orphan*/ * ddev; int /*<<< orphan*/  vxlan_del_task; int /*<<< orphan*/  vxlan_add_task; int /*<<< orphan*/  linkstate_task; int /*<<< orphan*/  watchdog_task; int /*<<< orphan*/  rx_mode_task; int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  counter_index; } ;
struct mlx4_en_port_profile {int /*<<< orphan*/  rx_ppp; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_ppp; int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_ring_num; int /*<<< orphan*/ * tx_ring_num; int /*<<< orphan*/  flags; } ;
struct TYPE_25__ {TYPE_6__* prof; int /*<<< orphan*/  max_num_tx_rings_p_up; } ;
struct mlx4_en_dev {TYPE_8__* dev; TYPE_7__ profile; int /*<<< orphan*/  workqueue; int /*<<< orphan*/ ** upper; struct net_device** pndev; scalar_t__ LSO_support; TYPE_3__* pdev; } ;
struct mlx4_en_cq {int dummy; } ;
struct TYPE_23__ {int cqe_size; int* rx_checksum_flags_port; int flags2; int flags; scalar_t__ steering_mode; scalar_t__ dmfs_high_steer_mode; scalar_t__ tunnel_offload_mode; int /*<<< orphan*/ * def_mac; int /*<<< orphan*/ * eth_mtu_cap; } ;
struct TYPE_26__ {int port_random_macs; TYPE_5__ caps; TYPE_2__* persist; } ;
struct TYPE_24__ {int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  tx_ppp; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  rx_ppp; } ;
struct TYPE_21__ {int /*<<< orphan*/  dev; } ;
struct TYPE_20__ {TYPE_1__* pdev; } ;
struct TYPE_19__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DS_SIZE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ ETH_FCS_LEN ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 void* ETH_RSS_HASH_TOP ; 
 void* ETH_RSS_HASH_XOR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HWTSTAMP_FILTER_NONE ; 
 int /*<<< orphan*/  HWTSTAMP_TX_OFF ; 
 int /*<<< orphan*/  IFF_UNICAST_FLT ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_RX_RINGS ; 
 int /*<<< orphan*/  MAX_TX_RINGS ; 
 int MLX4_DEV_CAP_FLAG2_IGNORE_FCS ; 
 int MLX4_DEV_CAP_FLAG2_PHV_EN ; 
 int MLX4_DEV_CAP_FLAG2_RSS_TOP ; 
 int MLX4_DEV_CAP_FLAG2_RSS_XOR ; 
 int MLX4_DEV_CAP_FLAG2_SKIP_OUTER_VLAN ; 
 int MLX4_DEV_CAP_FLAG2_TS ; 
 int MLX4_DEV_CAP_FLAG_FCS_KEEP ; 
 int /*<<< orphan*/  MLX4_EN_DEFAULT_TX_WORK ; 
 int /*<<< orphan*/  MLX4_EN_FLAG_RX_CSUM_NON_TCP_UDP ; 
 int MLX4_EN_MAC_HASH_SIZE ; 
 int MLX4_EN_MAX_RX_FRAGS ; 
 int /*<<< orphan*/  MLX4_EN_MSG_LEVEL ; 
 int MLX4_EN_NUM_TX_TYPES ; 
 int /*<<< orphan*/  MLX4_EN_PAGE_SIZE ; 
 int /*<<< orphan*/  MLX4_EN_PRIV_FLAGS_BLUEFLAME ; 
 int /*<<< orphan*/  MLX4_EN_PRIV_FLAGS_PHV ; 
 int /*<<< orphan*/  MLX4_EN_WATCHDOG_TIMEOUT ; 
 int MLX4_RX_CSUM_MODE_VAL_NON_TCP_UDP ; 
 int /*<<< orphan*/  MLX4_SINK_COUNTER_INDEX (TYPE_8__*) ; 
 scalar_t__ MLX4_STEERING_DMFS_A0_STATIC ; 
 scalar_t__ MLX4_STEERING_MODE_A0 ; 
 scalar_t__ MLX4_STEERING_MODE_DEVICE_MANAGED ; 
 scalar_t__ MLX4_TUNNEL_OFFLOAD_MODE_VXLAN ; 
 int MLX4_WQE_CTRL_CQ_UPDATE ; 
 int MLX4_WQE_CTRL_SOLICITED ; 
 int NETIF_F_GSO_PARTIAL ; 
 int NETIF_F_GSO_UDP_TUNNEL ; 
 int NETIF_F_GSO_UDP_TUNNEL_CSUM ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_HW_VLAN_STAG_FILTER ; 
 int NETIF_F_HW_VLAN_STAG_RX ; 
 int NETIF_F_HW_VLAN_STAG_TX ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_LOOPBACK ; 
 int NETIF_F_NTUPLE ; 
 int NETIF_F_RXALL ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_RXFCS ; 
 int NETIF_F_RXHASH ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int /*<<< orphan*/  NET_ADDR_RANDOM ; 
 int /*<<< orphan*/  SERVICE_TASK_DELAY ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATS_DELAY ; 
 size_t TX ; 
 int /*<<< orphan*/  VXLAN_STEER_BY_OUTER_MAC ; 
 struct net_device* alloc_etherdev_mqs (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  devlink_port_type_eth_set (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*,...) ; 
 int /*<<< orphan*/  en_warn (struct mlx4_en_priv*,char*,...) ; 
 int get_phv_bit (TYPE_8__*,int,int*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 void* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct mlx4_en_priv*,int /*<<< orphan*/ ,int) ; 
 int mlx4_INIT_PORT (TYPE_8__*,int) ; 
 int mlx4_SET_PORT_VXLAN (TYPE_8__*,int,int /*<<< orphan*/ ,int) ; 
 int mlx4_SET_PORT_general (TYPE_8__*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_alloc_hwq_res (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_en_add_vxlan_offloads ; 
 int mlx4_en_alloc_resources (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_calc_rx_buf (struct net_device*) ; 
 int /*<<< orphan*/  mlx4_en_del_vxlan_offloads ; 
 int /*<<< orphan*/  mlx4_en_destroy_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mlx4_en_do_get_stats ; 
 int /*<<< orphan*/  mlx4_en_do_set_rx_mode ; 
 int /*<<< orphan*/  mlx4_en_ethtool_ops ; 
 int /*<<< orphan*/  mlx4_en_init_timestamp (struct mlx4_en_dev*) ; 
 int /*<<< orphan*/  mlx4_en_linkstate ; 
 int /*<<< orphan*/  mlx4_en_restart ; 
 int /*<<< orphan*/  mlx4_en_service_task ; 
 int /*<<< orphan*/  mlx4_en_set_default_moderation (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_set_stats_bitmap (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_en_u64_to_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_en_update_loopback_state (struct net_device*,int) ; 
 int /*<<< orphan*/  mlx4_get_devlink_port (TYPE_8__*,size_t) ; 
 int mlx4_get_is_vlan_offload_disabled (TYPE_8__*,int,int*) ; 
 scalar_t__ mlx4_is_master (TYPE_8__*) ; 
 scalar_t__ mlx4_is_slave (TYPE_8__*) ; 
 int /*<<< orphan*/  mlx4_netdev_ops ; 
 int /*<<< orphan*/  mlx4_netdev_ops_master ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_rss_key_fill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_set_real_num_rx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_set_real_num_tx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mlx4_en_init_netdev(struct mlx4_en_dev *mdev, int port,
			struct mlx4_en_port_profile *prof)
{
	struct net_device *dev;
	struct mlx4_en_priv *priv;
	int i, t;
	int err;

	dev = alloc_etherdev_mqs(sizeof(struct mlx4_en_priv),
				 MAX_TX_RINGS, MAX_RX_RINGS);
	if (dev == NULL)
		return -ENOMEM;

	netif_set_real_num_tx_queues(dev, prof->tx_ring_num[TX]);
	netif_set_real_num_rx_queues(dev, prof->rx_ring_num);

	SET_NETDEV_DEV(dev, &mdev->dev->persist->pdev->dev);
	dev->dev_port = port - 1;

	/*
	 * Initialize driver private data
	 */

	priv = netdev_priv(dev);
	memset(priv, 0, sizeof(struct mlx4_en_priv));
	priv->counter_index = MLX4_SINK_COUNTER_INDEX(mdev->dev);
	spin_lock_init(&priv->stats_lock);
	INIT_WORK(&priv->rx_mode_task, mlx4_en_do_set_rx_mode);
	INIT_WORK(&priv->watchdog_task, mlx4_en_restart);
	INIT_WORK(&priv->linkstate_task, mlx4_en_linkstate);
	INIT_DELAYED_WORK(&priv->stats_task, mlx4_en_do_get_stats);
	INIT_DELAYED_WORK(&priv->service_task, mlx4_en_service_task);
	INIT_WORK(&priv->vxlan_add_task, mlx4_en_add_vxlan_offloads);
	INIT_WORK(&priv->vxlan_del_task, mlx4_en_del_vxlan_offloads);
#ifdef CONFIG_RFS_ACCEL
	INIT_LIST_HEAD(&priv->filters);
	spin_lock_init(&priv->filters_lock);
#endif

	priv->dev = dev;
	priv->mdev = mdev;
	priv->ddev = &mdev->pdev->dev;
	priv->prof = prof;
	priv->port = port;
	priv->port_up = false;
	priv->flags = prof->flags;
	priv->pflags = MLX4_EN_PRIV_FLAGS_BLUEFLAME;
	priv->ctrl_flags = cpu_to_be32(MLX4_WQE_CTRL_CQ_UPDATE |
			MLX4_WQE_CTRL_SOLICITED);
	priv->num_tx_rings_p_up = mdev->profile.max_num_tx_rings_p_up;
	priv->tx_work_limit = MLX4_EN_DEFAULT_TX_WORK;
	netdev_rss_key_fill(priv->rss_key, sizeof(priv->rss_key));

	for (t = 0; t < MLX4_EN_NUM_TX_TYPES; t++) {
		priv->tx_ring_num[t] = prof->tx_ring_num[t];
		if (!priv->tx_ring_num[t])
			continue;

		priv->tx_ring[t] = kcalloc(MAX_TX_RINGS,
					   sizeof(struct mlx4_en_tx_ring *),
					   GFP_KERNEL);
		if (!priv->tx_ring[t]) {
			err = -ENOMEM;
			goto out;
		}
		priv->tx_cq[t] = kcalloc(MAX_TX_RINGS,
					 sizeof(struct mlx4_en_cq *),
					 GFP_KERNEL);
		if (!priv->tx_cq[t]) {
			err = -ENOMEM;
			goto out;
		}
	}
	priv->rx_ring_num = prof->rx_ring_num;
	priv->cqe_factor = (mdev->dev->caps.cqe_size == 64) ? 1 : 0;
	priv->cqe_size = mdev->dev->caps.cqe_size;
	priv->mac_index = -1;
	priv->msg_enable = MLX4_EN_MSG_LEVEL;
#ifdef CONFIG_MLX4_EN_DCB
	if (!mlx4_is_slave(priv->mdev->dev)) {
		u8 prio;

		for (prio = 0; prio < IEEE_8021QAZ_MAX_TCS; ++prio) {
			priv->ets.prio_tc[prio] = prio;
			priv->ets.tc_tsa[prio]  = IEEE_8021QAZ_TSA_VENDOR;
		}

		priv->dcbx_cap = DCB_CAP_DCBX_VER_CEE | DCB_CAP_DCBX_HOST |
			DCB_CAP_DCBX_VER_IEEE;
		priv->flags |= MLX4_EN_DCB_ENABLED;
		priv->cee_config.pfc_state = false;

		for (i = 0; i < MLX4_EN_NUM_UP_HIGH; i++)
			priv->cee_config.dcb_pfc[i] = pfc_disabled;

		if (mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_ETS_CFG) {
			dev->dcbnl_ops = &mlx4_en_dcbnl_ops;
		} else {
			en_info(priv, "enabling only PFC DCB ops\n");
			dev->dcbnl_ops = &mlx4_en_dcbnl_pfc_ops;
		}
	}
#endif

	for (i = 0; i < MLX4_EN_MAC_HASH_SIZE; ++i)
		INIT_HLIST_HEAD(&priv->mac_hash[i]);

	/* Query for default mac and max mtu */
	priv->max_mtu = mdev->dev->caps.eth_mtu_cap[priv->port];

	if (mdev->dev->caps.rx_checksum_flags_port[priv->port] &
	    MLX4_RX_CSUM_MODE_VAL_NON_TCP_UDP)
		priv->flags |= MLX4_EN_FLAG_RX_CSUM_NON_TCP_UDP;

	/* Set default MAC */
	dev->addr_len = ETH_ALEN;
	mlx4_en_u64_to_mac(dev->dev_addr, mdev->dev->caps.def_mac[priv->port]);
	if (!is_valid_ether_addr(dev->dev_addr)) {
		en_err(priv, "Port: %d, invalid mac burned: %pM, quiting\n",
		       priv->port, dev->dev_addr);
		err = -EINVAL;
		goto out;
	} else if (mlx4_is_slave(priv->mdev->dev) &&
		   (priv->mdev->dev->port_random_macs & 1 << priv->port)) {
		/* Random MAC was assigned in mlx4_slave_cap
		 * in mlx4_core module
		 */
		dev->addr_assign_type |= NET_ADDR_RANDOM;
		en_warn(priv, "Assigned random MAC address %pM\n", dev->dev_addr);
	}

	memcpy(priv->current_mac, dev->dev_addr, sizeof(priv->current_mac));

	priv->stride = roundup_pow_of_two(sizeof(struct mlx4_en_rx_desc) +
					  DS_SIZE * MLX4_EN_MAX_RX_FRAGS);
	err = mlx4_en_alloc_resources(priv);
	if (err)
		goto out;

	/* Initialize time stamping config */
	priv->hwtstamp_config.flags = 0;
	priv->hwtstamp_config.tx_type = HWTSTAMP_TX_OFF;
	priv->hwtstamp_config.rx_filter = HWTSTAMP_FILTER_NONE;

	/* Allocate page for receive rings */
	err = mlx4_alloc_hwq_res(mdev->dev, &priv->res,
				MLX4_EN_PAGE_SIZE);
	if (err) {
		en_err(priv, "Failed to allocate page for rx qps\n");
		goto out;
	}
	priv->allocated = 1;

	/*
	 * Initialize netdev entry points
	 */
	if (mlx4_is_master(priv->mdev->dev))
		dev->netdev_ops = &mlx4_netdev_ops_master;
	else
		dev->netdev_ops = &mlx4_netdev_ops;
	dev->watchdog_timeo = MLX4_EN_WATCHDOG_TIMEOUT;
	netif_set_real_num_tx_queues(dev, priv->tx_ring_num[TX]);
	netif_set_real_num_rx_queues(dev, priv->rx_ring_num);

	dev->ethtool_ops = &mlx4_en_ethtool_ops;

	/*
	 * Set driver features
	 */
	dev->hw_features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
	if (mdev->LSO_support)
		dev->hw_features |= NETIF_F_TSO | NETIF_F_TSO6;

	dev->vlan_features = dev->hw_features;

	dev->hw_features |= NETIF_F_RXCSUM | NETIF_F_RXHASH;
	dev->features = dev->hw_features | NETIF_F_HIGHDMA |
			NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX |
			NETIF_F_HW_VLAN_CTAG_FILTER;
	dev->hw_features |= NETIF_F_LOOPBACK |
			NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX;

	if (!(mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_SKIP_OUTER_VLAN)) {
		dev->features |= NETIF_F_HW_VLAN_STAG_RX |
			NETIF_F_HW_VLAN_STAG_FILTER;
		dev->hw_features |= NETIF_F_HW_VLAN_STAG_RX;
	}

	if (mlx4_is_slave(mdev->dev)) {
		bool vlan_offload_disabled;
		int phv;

		err = get_phv_bit(mdev->dev, port, &phv);
		if (!err && phv) {
			dev->hw_features |= NETIF_F_HW_VLAN_STAG_TX;
			priv->pflags |= MLX4_EN_PRIV_FLAGS_PHV;
		}
		err = mlx4_get_is_vlan_offload_disabled(mdev->dev, port,
							&vlan_offload_disabled);
		if (!err && vlan_offload_disabled) {
			dev->hw_features &= ~(NETIF_F_HW_VLAN_CTAG_TX |
					      NETIF_F_HW_VLAN_CTAG_RX |
					      NETIF_F_HW_VLAN_STAG_TX |
					      NETIF_F_HW_VLAN_STAG_RX);
			dev->features &= ~(NETIF_F_HW_VLAN_CTAG_TX |
					   NETIF_F_HW_VLAN_CTAG_RX |
					   NETIF_F_HW_VLAN_STAG_TX |
					   NETIF_F_HW_VLAN_STAG_RX);
		}
	} else {
		if (mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_PHV_EN &&
		    !(mdev->dev->caps.flags2 &
		      MLX4_DEV_CAP_FLAG2_SKIP_OUTER_VLAN))
			dev->hw_features |= NETIF_F_HW_VLAN_STAG_TX;
	}

	if (mdev->dev->caps.flags & MLX4_DEV_CAP_FLAG_FCS_KEEP)
		dev->hw_features |= NETIF_F_RXFCS;

	if (mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_IGNORE_FCS)
		dev->hw_features |= NETIF_F_RXALL;

	if (mdev->dev->caps.steering_mode ==
	    MLX4_STEERING_MODE_DEVICE_MANAGED &&
	    mdev->dev->caps.dmfs_high_steer_mode != MLX4_STEERING_DMFS_A0_STATIC)
		dev->hw_features |= NETIF_F_NTUPLE;

	if (mdev->dev->caps.steering_mode != MLX4_STEERING_MODE_A0)
		dev->priv_flags |= IFF_UNICAST_FLT;

	/* Setting a default hash function value */
	if (mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_RSS_TOP) {
		priv->rss_hash_fn = ETH_RSS_HASH_TOP;
	} else if (mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_RSS_XOR) {
		priv->rss_hash_fn = ETH_RSS_HASH_XOR;
	} else {
		en_warn(priv,
			"No RSS hash capabilities exposed, using Toeplitz\n");
		priv->rss_hash_fn = ETH_RSS_HASH_TOP;
	}

	if (mdev->dev->caps.tunnel_offload_mode == MLX4_TUNNEL_OFFLOAD_MODE_VXLAN) {
		dev->hw_features |= NETIF_F_GSO_UDP_TUNNEL |
				    NETIF_F_GSO_UDP_TUNNEL_CSUM |
				    NETIF_F_GSO_PARTIAL;
		dev->features    |= NETIF_F_GSO_UDP_TUNNEL |
				    NETIF_F_GSO_UDP_TUNNEL_CSUM |
				    NETIF_F_GSO_PARTIAL;
		dev->gso_partial_features = NETIF_F_GSO_UDP_TUNNEL_CSUM;
	}

	/* MTU range: 68 - hw-specific max */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = priv->max_mtu;

	mdev->pndev[port] = dev;
	mdev->upper[port] = NULL;

	netif_carrier_off(dev);
	mlx4_en_set_default_moderation(priv);

	en_warn(priv, "Using %d TX rings\n", prof->tx_ring_num[TX]);
	en_warn(priv, "Using %d RX rings\n", prof->rx_ring_num);

	mlx4_en_update_loopback_state(priv->dev, priv->dev->features);

	/* Configure port */
	mlx4_en_calc_rx_buf(dev);
	err = mlx4_SET_PORT_general(mdev->dev, priv->port,
				    priv->rx_skb_size + ETH_FCS_LEN,
				    prof->tx_pause, prof->tx_ppp,
				    prof->rx_pause, prof->rx_ppp);
	if (err) {
		en_err(priv, "Failed setting port general configurations for port %d, with error %d\n",
		       priv->port, err);
		goto out;
	}

	if (mdev->dev->caps.tunnel_offload_mode == MLX4_TUNNEL_OFFLOAD_MODE_VXLAN) {
		err = mlx4_SET_PORT_VXLAN(mdev->dev, priv->port, VXLAN_STEER_BY_OUTER_MAC, 1);
		if (err) {
			en_err(priv, "Failed setting port L2 tunnel configuration, err %d\n",
			       err);
			goto out;
		}
	}

	/* Init port */
	en_warn(priv, "Initializing port\n");
	err = mlx4_INIT_PORT(mdev->dev, priv->port);
	if (err) {
		en_err(priv, "Failed Initializing port\n");
		goto out;
	}
	queue_delayed_work(mdev->workqueue, &priv->stats_task, STATS_DELAY);

	/* Initialize time stamp mechanism */
	if (mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_TS)
		mlx4_en_init_timestamp(mdev);

	queue_delayed_work(mdev->workqueue, &priv->service_task,
			   SERVICE_TASK_DELAY);

	mlx4_en_set_stats_bitmap(mdev->dev, &priv->stats_bitmap,
				 mdev->profile.prof[priv->port].rx_ppp,
				 mdev->profile.prof[priv->port].rx_pause,
				 mdev->profile.prof[priv->port].tx_ppp,
				 mdev->profile.prof[priv->port].tx_pause);

	err = register_netdev(dev);
	if (err) {
		en_err(priv, "Netdev registration failed for port %d\n", port);
		goto out;
	}

	priv->registered = 1;
	devlink_port_type_eth_set(mlx4_get_devlink_port(mdev->dev, priv->port),
				  dev);

	return 0;

out:
	mlx4_en_destroy_netdev(dev);
	return err;
}