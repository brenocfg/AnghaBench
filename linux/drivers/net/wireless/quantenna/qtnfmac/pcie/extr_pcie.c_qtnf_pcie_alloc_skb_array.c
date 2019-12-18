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
struct sk_buff {int dummy; } ;
struct qtnf_pcie_bus_priv {int tx_bd_num; int rx_bd_num; struct sk_buff** rx_skb; struct sk_buff** tx_skb; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sk_buff** devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int qtnf_pcie_alloc_skb_array(struct qtnf_pcie_bus_priv *priv)
{
	struct sk_buff **vaddr;
	int len;

	len = priv->tx_bd_num * sizeof(*priv->tx_skb) +
		priv->rx_bd_num * sizeof(*priv->rx_skb);
	vaddr = devm_kzalloc(&priv->pdev->dev, len, GFP_KERNEL);

	if (!vaddr)
		return -ENOMEM;

	priv->tx_skb = vaddr;

	vaddr += priv->tx_bd_num;
	priv->rx_skb = vaddr;

	return 0;
}