#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct net_device {int /*<<< orphan*/  mtu; } ;
struct mlx4_en_tx_ring {int buf_size; scalar_t__ buf; int /*<<< orphan*/ * recycle_ring; int /*<<< orphan*/  tx_queue; } ;
struct TYPE_16__ {int /*<<< orphan*/  indir_qp; } ;
struct mlx4_en_priv {int port_up; int rx_ring_num; int cqe_factor; size_t port; int num_tx_rings_p_up; int* tx_ring_num; int flags; TYPE_8__** rx_ring; struct mlx4_en_cq** rx_cq; struct mlx4_en_cq*** tx_cq; struct mlx4_en_tx_ring*** tx_ring; struct mlx4_en_dev* mdev; int /*<<< orphan*/  rx_mode_task; int /*<<< orphan*/  broadcast_id; TYPE_3__ rss_map; int /*<<< orphan*/  base_qpn; TYPE_2__* prof; scalar_t__ rx_skb_size; int /*<<< orphan*/  counter_index; int /*<<< orphan*/  cqe_size; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/ * ethtool_rules; int /*<<< orphan*/  ethtool_list; int /*<<< orphan*/  curr_list; int /*<<< orphan*/  mc_list; } ;
struct mlx4_en_dev {TYPE_5__* dev; int /*<<< orphan*/  workqueue; scalar_t__* mac_removed; } ;
struct TYPE_14__ {int /*<<< orphan*/  cqn; } ;
struct mlx4_en_cq {int size; int /*<<< orphan*/  napi; TYPE_1__ mcq; TYPE_7__* buf; } ;
struct mlx4_cqe {int /*<<< orphan*/  owner_sr_opcode; } ;
struct ethtool_flow_id {int dummy; } ;
struct TYPE_20__ {int /*<<< orphan*/  cqn; } ;
struct TYPE_19__ {int /*<<< orphan*/  wqe_index; } ;
struct TYPE_17__ {scalar_t__ tunnel_offload_mode; scalar_t__ steering_mode; } ;
struct TYPE_18__ {TYPE_4__ caps; } ;
struct TYPE_15__ {int /*<<< orphan*/  rx_ppp; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_ppp; int /*<<< orphan*/  tx_pause; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 scalar_t__ ETH_FCS_LEN ; 
 int /*<<< orphan*/  HW ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MAX_NUM_OF_FS_RULES ; 
 int /*<<< orphan*/  MLX4_CQE_OWNER_MASK ; 
 int MLX4_EN_FLAG_MC_PROMISC ; 
 int MLX4_EN_FLAG_PROMISC ; 
 int MLX4_EN_NUM_TX_TYPES ; 
 int /*<<< orphan*/  MLX4_PROT_ETH ; 
 scalar_t__ MLX4_STEERING_MODE_A0 ; 
 scalar_t__ MLX4_TUNNEL_OFFLOAD_MODE_VXLAN ; 
 scalar_t__ STAMP_STRIDE ; 
 int TX ; 
 int TX_XDP ; 
 int /*<<< orphan*/  VXLAN_STEER_BY_OUTER_MAC ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,...) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*,...) ; 
 int /*<<< orphan*/  eth_broadcast_addr (int*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_INIT_PORT (TYPE_5__*,size_t) ; 
 int mlx4_SET_PORT_VXLAN (TYPE_5__*,size_t,int /*<<< orphan*/ ,int) ; 
 int mlx4_SET_PORT_general (TYPE_5__*,size_t,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_SET_PORT_qpn_calc (TYPE_5__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_SET_PORT_user_mtu (TYPE_5__*,size_t,int /*<<< orphan*/ ) ; 
 int mlx4_en_activate_cq (struct mlx4_en_priv*,struct mlx4_en_cq*,int) ; 
 int mlx4_en_activate_rx_rings (struct mlx4_en_priv*) ; 
 int mlx4_en_activate_tx_ring (struct mlx4_en_priv*,struct mlx4_en_tx_ring*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx4_en_arm_cq (struct mlx4_en_priv*,struct mlx4_en_cq*) ; 
 int /*<<< orphan*/  mlx4_en_calc_rx_buf (struct net_device*) ; 
 int mlx4_en_config_rss_steer (struct mlx4_en_priv*) ; 
 int mlx4_en_create_drop_qp (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_deactivate_cq (struct mlx4_en_priv*,struct mlx4_en_cq*) ; 
 int /*<<< orphan*/  mlx4_en_deactivate_rx_ring (struct mlx4_en_priv*,TYPE_8__*) ; 
 int /*<<< orphan*/  mlx4_en_deactivate_tx_ring (struct mlx4_en_priv*,struct mlx4_en_tx_ring*) ; 
 int /*<<< orphan*/  mlx4_en_destroy_drop_qp (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_free_affinity_hint (struct mlx4_en_priv*,int) ; 
 struct mlx4_cqe* mlx4_en_get_cqe (TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 int mlx4_en_get_qp (struct mlx4_en_priv*) ; 
 int mlx4_en_init_affinity_hint (struct mlx4_en_priv*,int) ; 
 int /*<<< orphan*/  mlx4_en_init_recycle_ring (struct mlx4_en_priv*,int) ; 
 int /*<<< orphan*/  mlx4_en_init_tx_xdp_ring_descs (struct mlx4_en_priv*,struct mlx4_en_tx_ring*) ; 
 int /*<<< orphan*/  mlx4_en_put_qp (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_release_rss_steer (struct mlx4_en_priv*) ; 
 int mlx4_en_set_cq_moder (struct mlx4_en_priv*,struct mlx4_en_cq*) ; 
 scalar_t__ mlx4_en_set_rss_steer_rules (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_get_default_counter_index (TYPE_5__*,size_t) ; 
 scalar_t__ mlx4_multicast_attach (TYPE_5__*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_en_dev*,char*) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_get_tx_queue (struct net_device*,int) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udp_tunnel_get_rx_info (struct net_device*) ; 

int mlx4_en_start_port(struct net_device *dev)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;
	struct mlx4_en_cq *cq;
	struct mlx4_en_tx_ring *tx_ring;
	int rx_index = 0;
	int err = 0;
	int i, t;
	int j;
	u8 mc_list[16] = {0};

	if (priv->port_up) {
		en_dbg(DRV, priv, "start port called while port already up\n");
		return 0;
	}

	INIT_LIST_HEAD(&priv->mc_list);
	INIT_LIST_HEAD(&priv->curr_list);
	INIT_LIST_HEAD(&priv->ethtool_list);
	memset(&priv->ethtool_rules[0], 0,
	       sizeof(struct ethtool_flow_id) * MAX_NUM_OF_FS_RULES);

	/* Calculate Rx buf size */
	dev->mtu = min(dev->mtu, priv->max_mtu);
	mlx4_en_calc_rx_buf(dev);
	en_dbg(DRV, priv, "Rx buf size:%d\n", priv->rx_skb_size);

	/* Configure rx cq's and rings */
	err = mlx4_en_activate_rx_rings(priv);
	if (err) {
		en_err(priv, "Failed to activate RX rings\n");
		return err;
	}
	for (i = 0; i < priv->rx_ring_num; i++) {
		cq = priv->rx_cq[i];

		err = mlx4_en_init_affinity_hint(priv, i);
		if (err) {
			en_err(priv, "Failed preparing IRQ affinity hint\n");
			goto cq_err;
		}

		err = mlx4_en_activate_cq(priv, cq, i);
		if (err) {
			en_err(priv, "Failed activating Rx CQ\n");
			mlx4_en_free_affinity_hint(priv, i);
			goto cq_err;
		}

		for (j = 0; j < cq->size; j++) {
			struct mlx4_cqe *cqe = NULL;

			cqe = mlx4_en_get_cqe(cq->buf, j, priv->cqe_size) +
			      priv->cqe_factor;
			cqe->owner_sr_opcode = MLX4_CQE_OWNER_MASK;
		}

		err = mlx4_en_set_cq_moder(priv, cq);
		if (err) {
			en_err(priv, "Failed setting cq moderation parameters\n");
			mlx4_en_deactivate_cq(priv, cq);
			mlx4_en_free_affinity_hint(priv, i);
			goto cq_err;
		}
		mlx4_en_arm_cq(priv, cq);
		priv->rx_ring[i]->cqn = cq->mcq.cqn;
		++rx_index;
	}

	/* Set qp number */
	en_dbg(DRV, priv, "Getting qp number for port %d\n", priv->port);
	err = mlx4_en_get_qp(priv);
	if (err) {
		en_err(priv, "Failed getting eth qp\n");
		goto cq_err;
	}
	mdev->mac_removed[priv->port] = 0;

	priv->counter_index =
			mlx4_get_default_counter_index(mdev->dev, priv->port);

	err = mlx4_en_config_rss_steer(priv);
	if (err) {
		en_err(priv, "Failed configuring rss steering\n");
		goto mac_err;
	}

	err = mlx4_en_create_drop_qp(priv);
	if (err)
		goto rss_err;

	/* Configure tx cq's and rings */
	for (t = 0 ; t < MLX4_EN_NUM_TX_TYPES; t++) {
		u8 num_tx_rings_p_up = t == TX ?
			priv->num_tx_rings_p_up : priv->tx_ring_num[t];

		for (i = 0; i < priv->tx_ring_num[t]; i++) {
			/* Configure cq */
			cq = priv->tx_cq[t][i];
			err = mlx4_en_activate_cq(priv, cq, i);
			if (err) {
				en_err(priv, "Failed allocating Tx CQ\n");
				goto tx_err;
			}
			err = mlx4_en_set_cq_moder(priv, cq);
			if (err) {
				en_err(priv, "Failed setting cq moderation parameters\n");
				mlx4_en_deactivate_cq(priv, cq);
				goto tx_err;
			}
			en_dbg(DRV, priv,
			       "Resetting index of collapsed CQ:%d to -1\n", i);
			cq->buf->wqe_index = cpu_to_be16(0xffff);

			/* Configure ring */
			tx_ring = priv->tx_ring[t][i];
			err = mlx4_en_activate_tx_ring(priv, tx_ring,
						       cq->mcq.cqn,
						       i / num_tx_rings_p_up);
			if (err) {
				en_err(priv, "Failed allocating Tx ring\n");
				mlx4_en_deactivate_cq(priv, cq);
				goto tx_err;
			}
			if (t != TX_XDP) {
				tx_ring->tx_queue = netdev_get_tx_queue(dev, i);
				tx_ring->recycle_ring = NULL;

				/* Arm CQ for TX completions */
				mlx4_en_arm_cq(priv, cq);

			} else {
				mlx4_en_init_tx_xdp_ring_descs(priv, tx_ring);
				mlx4_en_init_recycle_ring(priv, i);
				/* XDP TX CQ should never be armed */
			}

			/* Set initial ownership of all Tx TXBBs to SW (1) */
			for (j = 0; j < tx_ring->buf_size; j += STAMP_STRIDE)
				*((u32 *)(tx_ring->buf + j)) = 0xffffffff;
		}
	}

	/* Configure port */
	err = mlx4_SET_PORT_general(mdev->dev, priv->port,
				    priv->rx_skb_size + ETH_FCS_LEN,
				    priv->prof->tx_pause,
				    priv->prof->tx_ppp,
				    priv->prof->rx_pause,
				    priv->prof->rx_ppp);
	if (err) {
		en_err(priv, "Failed setting port general configurations for port %d, with error %d\n",
		       priv->port, err);
		goto tx_err;
	}

	err = mlx4_SET_PORT_user_mtu(mdev->dev, priv->port, dev->mtu);
	if (err) {
		en_err(priv, "Failed to pass user MTU(%d) to Firmware for port %d, with error %d\n",
		       dev->mtu, priv->port, err);
		goto tx_err;
	}

	/* Set default qp number */
	err = mlx4_SET_PORT_qpn_calc(mdev->dev, priv->port, priv->base_qpn, 0);
	if (err) {
		en_err(priv, "Failed setting default qp numbers\n");
		goto tx_err;
	}

	if (mdev->dev->caps.tunnel_offload_mode == MLX4_TUNNEL_OFFLOAD_MODE_VXLAN) {
		err = mlx4_SET_PORT_VXLAN(mdev->dev, priv->port, VXLAN_STEER_BY_OUTER_MAC, 1);
		if (err) {
			en_err(priv, "Failed setting port L2 tunnel configuration, err %d\n",
			       err);
			goto tx_err;
		}
	}

	/* Init port */
	en_dbg(HW, priv, "Initializing port\n");
	err = mlx4_INIT_PORT(mdev->dev, priv->port);
	if (err) {
		en_err(priv, "Failed Initializing port\n");
		goto tx_err;
	}

	/* Set Unicast and VXLAN steering rules */
	if (mdev->dev->caps.steering_mode != MLX4_STEERING_MODE_A0 &&
	    mlx4_en_set_rss_steer_rules(priv))
		mlx4_warn(mdev, "Failed setting steering rules\n");

	/* Attach rx QP to bradcast address */
	eth_broadcast_addr(&mc_list[10]);
	mc_list[5] = priv->port; /* needed for B0 steering support */
	if (mlx4_multicast_attach(mdev->dev, priv->rss_map.indir_qp, mc_list,
				  priv->port, 0, MLX4_PROT_ETH,
				  &priv->broadcast_id))
		mlx4_warn(mdev, "Failed Attaching Broadcast\n");

	/* Must redo promiscuous mode setup. */
	priv->flags &= ~(MLX4_EN_FLAG_PROMISC | MLX4_EN_FLAG_MC_PROMISC);

	/* Schedule multicast task to populate multicast list */
	queue_work(mdev->workqueue, &priv->rx_mode_task);

	if (priv->mdev->dev->caps.tunnel_offload_mode == MLX4_TUNNEL_OFFLOAD_MODE_VXLAN)
		udp_tunnel_get_rx_info(dev);

	priv->port_up = true;

	/* Process all completions if exist to prevent
	 * the queues freezing if they are full
	 */
	for (i = 0; i < priv->rx_ring_num; i++) {
		local_bh_disable();
		napi_schedule(&priv->rx_cq[i]->napi);
		local_bh_enable();
	}

	netif_tx_start_all_queues(dev);
	netif_device_attach(dev);

	return 0;

tx_err:
	if (t == MLX4_EN_NUM_TX_TYPES) {
		t--;
		i = priv->tx_ring_num[t];
	}
	while (t >= 0) {
		while (i--) {
			mlx4_en_deactivate_tx_ring(priv, priv->tx_ring[t][i]);
			mlx4_en_deactivate_cq(priv, priv->tx_cq[t][i]);
		}
		if (!t--)
			break;
		i = priv->tx_ring_num[t];
	}
	mlx4_en_destroy_drop_qp(priv);
rss_err:
	mlx4_en_release_rss_steer(priv);
mac_err:
	mlx4_en_put_qp(priv);
cq_err:
	while (rx_index--) {
		mlx4_en_deactivate_cq(priv, priv->rx_cq[rx_index]);
		mlx4_en_free_affinity_hint(priv, rx_index);
	}
	for (i = 0; i < priv->rx_ring_num; i++)
		mlx4_en_deactivate_rx_ring(priv, priv->rx_ring[i]);

	return err; /* need to close devices */
}