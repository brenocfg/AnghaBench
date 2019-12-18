#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_22__ {scalar_t__ map; int /*<<< orphan*/  buf; } ;
struct TYPE_23__ {TYPE_3__ direct; } ;
struct TYPE_18__ {TYPE_4__ buf; } ;
struct TYPE_19__ {TYPE_5__* uar; } ;
struct TYPE_17__ {int /*<<< orphan*/  event; } ;
struct mlx4_en_tx_ring {int size; int size_mask; int sp_stride; int full_size; int bf_enabled; int bf_alloced; int queue_index; int /*<<< orphan*/ * tx_info; struct mlx4_en_tx_ring* bounce_buf; int /*<<< orphan*/  buf_size; TYPE_12__ sp_wqres; int /*<<< orphan*/  qpn; int /*<<< orphan*/  sp_affinity_mask; int /*<<< orphan*/  hwtstamp_tx_type; TYPE_14__ bf; TYPE_10__ sp_qp; int /*<<< orphan*/  buf; } ;
struct mlx4_en_tx_info {int dummy; } ;
struct TYPE_25__ {int /*<<< orphan*/  tx_type; } ;
struct mlx4_en_priv {int pflags; int num_tx_rings_p_up; struct mlx4_en_dev* mdev; TYPE_6__ hwtstamp_config; } ;
struct TYPE_24__ {int /*<<< orphan*/  map; } ;
struct mlx4_en_dev {TYPE_7__* dev; int /*<<< orphan*/  uar_map; TYPE_5__ priv_uar; } ;
struct TYPE_26__ {int numa_node; TYPE_2__* persist; } ;
struct TYPE_21__ {TYPE_1__* pdev; } ;
struct TYPE_20__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HEADROOM ; 
 int /*<<< orphan*/  MAX_DESC_SIZE ; 
 int MAX_DESC_TXBBS ; 
 int /*<<< orphan*/  MLX4_EN_PAGE_SIZE ; 
 int MLX4_EN_PRIV_FLAGS_BLUEFLAME ; 
 int /*<<< orphan*/  MLX4_RESERVE_ETH_BF_QP ; 
 int /*<<< orphan*/  MLX4_RES_USAGE_DRIVER ; 
 int /*<<< orphan*/  cpumask_local_spread (int,int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,...) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*,...) ; 
 int /*<<< orphan*/  kfree (struct mlx4_en_tx_ring*) ; 
 struct mlx4_en_tx_ring* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx4_en_tx_ring* kmalloc_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kvmalloc_node (int,int /*<<< orphan*/ ,int) ; 
 struct mlx4_en_tx_ring* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int mlx4_alloc_hwq_res (TYPE_7__*,TYPE_12__*,int /*<<< orphan*/ ) ; 
 int mlx4_bf_alloc (TYPE_7__*,TYPE_14__*,int) ; 
 int /*<<< orphan*/  mlx4_en_sqp_event ; 
 int /*<<< orphan*/  mlx4_free_hwq_res (TYPE_7__*,TYPE_12__*,int /*<<< orphan*/ ) ; 
 int mlx4_qp_alloc (TYPE_7__*,int /*<<< orphan*/ ,TYPE_10__*) ; 
 int /*<<< orphan*/  mlx4_qp_release_range (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int mlx4_qp_reserve_range (TYPE_7__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dev_node (int /*<<< orphan*/ *,int) ; 

int mlx4_en_create_tx_ring(struct mlx4_en_priv *priv,
			   struct mlx4_en_tx_ring **pring, u32 size,
			   u16 stride, int node, int queue_index)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	struct mlx4_en_tx_ring *ring;
	int tmp;
	int err;

	ring = kzalloc_node(sizeof(*ring), GFP_KERNEL, node);
	if (!ring) {
		en_err(priv, "Failed allocating TX ring\n");
		return -ENOMEM;
	}

	ring->size = size;
	ring->size_mask = size - 1;
	ring->sp_stride = stride;
	ring->full_size = ring->size - HEADROOM - MAX_DESC_TXBBS;

	tmp = size * sizeof(struct mlx4_en_tx_info);
	ring->tx_info = kvmalloc_node(tmp, GFP_KERNEL, node);
	if (!ring->tx_info) {
		err = -ENOMEM;
		goto err_ring;
	}

	en_dbg(DRV, priv, "Allocated tx_info ring at addr:%p size:%d\n",
		 ring->tx_info, tmp);

	ring->bounce_buf = kmalloc_node(MAX_DESC_SIZE, GFP_KERNEL, node);
	if (!ring->bounce_buf) {
		ring->bounce_buf = kmalloc(MAX_DESC_SIZE, GFP_KERNEL);
		if (!ring->bounce_buf) {
			err = -ENOMEM;
			goto err_info;
		}
	}
	ring->buf_size = ALIGN(size * ring->sp_stride, MLX4_EN_PAGE_SIZE);

	/* Allocate HW buffers on provided NUMA node */
	set_dev_node(&mdev->dev->persist->pdev->dev, node);
	err = mlx4_alloc_hwq_res(mdev->dev, &ring->sp_wqres, ring->buf_size);
	set_dev_node(&mdev->dev->persist->pdev->dev, mdev->dev->numa_node);
	if (err) {
		en_err(priv, "Failed allocating hwq resources\n");
		goto err_bounce;
	}

	ring->buf = ring->sp_wqres.buf.direct.buf;

	en_dbg(DRV, priv, "Allocated TX ring (addr:%p) - buf:%p size:%d buf_size:%d dma:%llx\n",
	       ring, ring->buf, ring->size, ring->buf_size,
	       (unsigned long long) ring->sp_wqres.buf.direct.map);

	err = mlx4_qp_reserve_range(mdev->dev, 1, 1, &ring->qpn,
				    MLX4_RESERVE_ETH_BF_QP,
				    MLX4_RES_USAGE_DRIVER);
	if (err) {
		en_err(priv, "failed reserving qp for TX ring\n");
		goto err_hwq_res;
	}

	err = mlx4_qp_alloc(mdev->dev, ring->qpn, &ring->sp_qp);
	if (err) {
		en_err(priv, "Failed allocating qp %d\n", ring->qpn);
		goto err_reserve;
	}
	ring->sp_qp.event = mlx4_en_sqp_event;

	err = mlx4_bf_alloc(mdev->dev, &ring->bf, node);
	if (err) {
		en_dbg(DRV, priv, "working without blueflame (%d)\n", err);
		ring->bf.uar = &mdev->priv_uar;
		ring->bf.uar->map = mdev->uar_map;
		ring->bf_enabled = false;
		ring->bf_alloced = false;
		priv->pflags &= ~MLX4_EN_PRIV_FLAGS_BLUEFLAME;
	} else {
		ring->bf_alloced = true;
		ring->bf_enabled = !!(priv->pflags &
				      MLX4_EN_PRIV_FLAGS_BLUEFLAME);
	}

	ring->hwtstamp_tx_type = priv->hwtstamp_config.tx_type;
	ring->queue_index = queue_index;

	if (queue_index < priv->num_tx_rings_p_up)
		cpumask_set_cpu(cpumask_local_spread(queue_index,
						     priv->mdev->dev->numa_node),
				&ring->sp_affinity_mask);

	*pring = ring;
	return 0;

err_reserve:
	mlx4_qp_release_range(mdev->dev, ring->qpn, 1);
err_hwq_res:
	mlx4_free_hwq_res(mdev->dev, &ring->sp_wqres, ring->buf_size);
err_bounce:
	kfree(ring->bounce_buf);
	ring->bounce_buf = NULL;
err_info:
	kvfree(ring->tx_info);
	ring->tx_info = NULL;
err_ring:
	kfree(ring);
	*pring = NULL;
	return err;
}