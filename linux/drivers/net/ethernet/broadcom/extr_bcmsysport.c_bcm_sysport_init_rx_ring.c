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
struct bcm_sysport_priv {int num_rx_bds; int num_rx_desc_words; scalar_t__ rx_bds; int /*<<< orphan*/  netdev; struct bcm_sysport_cb* rx_cbs; scalar_t__ rx_read_ptr; scalar_t__ rx_c_index; scalar_t__ base; } ;
struct bcm_sysport_cb {scalar_t__ bd_addr; } ;

/* Variables and functions */
 int DESC_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RDMA_CONS_INDEX ; 
 int RDMA_DISABLED ; 
 int /*<<< orphan*/  RDMA_END_ADDR_HI ; 
 int /*<<< orphan*/  RDMA_END_ADDR_LO ; 
 int /*<<< orphan*/  RDMA_PROD_INDEX ; 
 int /*<<< orphan*/  RDMA_RING_BUF_SIZE ; 
 int RDMA_RING_SIZE_SHIFT ; 
 int /*<<< orphan*/  RDMA_START_ADDR_HI ; 
 int /*<<< orphan*/  RDMA_START_ADDR_LO ; 
 int /*<<< orphan*/  RDMA_STATUS ; 
 int /*<<< orphan*/  RDMA_WRITE_PTR_HI ; 
 int /*<<< orphan*/  RDMA_WRITE_PTR_LO ; 
 int RX_BUF_LENGTH ; 
 scalar_t__ SYS_PORT_RDMA_OFFSET ; 
 int WORDS_PER_DESC ; 
 int bcm_sysport_alloc_rx_bufs (struct bcm_sysport_priv*) ; 
 int /*<<< orphan*/  hw ; 
 struct bcm_sysport_cb* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct bcm_sysport_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  netif_err (struct bcm_sysport_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rdma_enable_set (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int rdma_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_writel (struct bcm_sysport_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_sysport_init_rx_ring(struct bcm_sysport_priv *priv)
{
	struct bcm_sysport_cb *cb;
	u32 reg;
	int ret;
	int i;

	/* Initialize SW view of the RX ring */
	priv->num_rx_bds = priv->num_rx_desc_words / WORDS_PER_DESC;
	priv->rx_bds = priv->base + SYS_PORT_RDMA_OFFSET;
	priv->rx_c_index = 0;
	priv->rx_read_ptr = 0;
	priv->rx_cbs = kcalloc(priv->num_rx_bds, sizeof(struct bcm_sysport_cb),
				GFP_KERNEL);
	if (!priv->rx_cbs) {
		netif_err(priv, hw, priv->netdev, "CB allocation failed\n");
		return -ENOMEM;
	}

	for (i = 0; i < priv->num_rx_bds; i++) {
		cb = priv->rx_cbs + i;
		cb->bd_addr = priv->rx_bds + i * DESC_SIZE;
	}

	ret = bcm_sysport_alloc_rx_bufs(priv);
	if (ret) {
		netif_err(priv, hw, priv->netdev, "SKB allocation failed\n");
		return ret;
	}

	/* Initialize HW, ensure RDMA is disabled */
	reg = rdma_readl(priv, RDMA_STATUS);
	if (!(reg & RDMA_DISABLED))
		rdma_enable_set(priv, 0);

	rdma_writel(priv, 0, RDMA_WRITE_PTR_LO);
	rdma_writel(priv, 0, RDMA_WRITE_PTR_HI);
	rdma_writel(priv, 0, RDMA_PROD_INDEX);
	rdma_writel(priv, 0, RDMA_CONS_INDEX);
	rdma_writel(priv, priv->num_rx_bds << RDMA_RING_SIZE_SHIFT |
			  RX_BUF_LENGTH, RDMA_RING_BUF_SIZE);
	/* Operate the queue in ring mode */
	rdma_writel(priv, 0, RDMA_START_ADDR_HI);
	rdma_writel(priv, 0, RDMA_START_ADDR_LO);
	rdma_writel(priv, 0, RDMA_END_ADDR_HI);
	rdma_writel(priv, priv->num_rx_desc_words - 1, RDMA_END_ADDR_LO);

	netif_dbg(priv, hw, priv->netdev,
		  "RDMA cfg, num_rx_bds=%d, rx_bds=%p\n",
		  priv->num_rx_bds, priv->rx_bds);

	return 0;
}