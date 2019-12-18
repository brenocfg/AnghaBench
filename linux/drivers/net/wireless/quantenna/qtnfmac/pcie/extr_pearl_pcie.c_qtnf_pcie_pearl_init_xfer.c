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
struct qtnf_pearl_tx_bd {int dummy; } ;
struct qtnf_pcie_bus_priv {unsigned int tx_bd_num; unsigned int rx_bd_num; scalar_t__ rx_bd_r_index; scalar_t__ rx_bd_w_index; } ;
struct qtnf_pcie_pearl_state {struct qtnf_pcie_bus_priv base; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int PCIE_HHBM_MAX_SIZE ; 
 void* PEARL_TX_BD_SIZE_DEFAULT ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned int) ; 
 int pearl_alloc_bd_table (struct qtnf_pcie_pearl_state*) ; 
 int pearl_alloc_rx_buffers (struct qtnf_pcie_pearl_state*) ; 
 int pearl_hhbm_init (struct qtnf_pcie_pearl_state*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int) ; 
 int qtnf_pcie_alloc_skb_array (struct qtnf_pcie_bus_priv*) ; 

__attribute__((used)) static int qtnf_pcie_pearl_init_xfer(struct qtnf_pcie_pearl_state *ps,
				     unsigned int tx_bd_size)
{
	struct qtnf_pcie_bus_priv *priv = &ps->base;
	int ret;
	u32 val;

	if (tx_bd_size == 0)
		tx_bd_size = PEARL_TX_BD_SIZE_DEFAULT;

	val = tx_bd_size * sizeof(struct qtnf_pearl_tx_bd);

	if (!is_power_of_2(tx_bd_size) || val > PCIE_HHBM_MAX_SIZE) {
		pr_warn("bad tx_bd_size value %u\n", tx_bd_size);
		priv->tx_bd_num = PEARL_TX_BD_SIZE_DEFAULT;
	} else {
		priv->tx_bd_num = tx_bd_size;
	}

	priv->rx_bd_w_index = 0;
	priv->rx_bd_r_index = 0;

	if (!priv->rx_bd_num || !is_power_of_2(priv->rx_bd_num)) {
		pr_err("rx_bd_size_param %u is not power of two\n",
		       priv->rx_bd_num);
		return -EINVAL;
	}

	val = priv->rx_bd_num * sizeof(dma_addr_t);
	if (val > PCIE_HHBM_MAX_SIZE) {
		pr_err("rx_bd_size_param %u is too large\n",
		       priv->rx_bd_num);
		return -EINVAL;
	}

	ret = pearl_hhbm_init(ps);
	if (ret) {
		pr_err("failed to init h/w queues\n");
		return ret;
	}

	ret = qtnf_pcie_alloc_skb_array(priv);
	if (ret) {
		pr_err("failed to allocate skb array\n");
		return ret;
	}

	ret = pearl_alloc_bd_table(ps);
	if (ret) {
		pr_err("failed to allocate bd table\n");
		return ret;
	}

	ret = pearl_alloc_rx_buffers(ps);
	if (ret) {
		pr_err("failed to allocate rx buffers\n");
		return ret;
	}

	return ret;
}