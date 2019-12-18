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
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  ring_phys; } ;
struct TYPE_3__ {int /*<<< orphan*/  ring_phys; } ;
struct ksz_hw {TYPE_2__ rx_desc_info; TYPE_1__ tx_desc_info; scalar_t__ multi_list_size; scalar_t__ all_multi; scalar_t__ promiscuous; } ;
struct dev_priv {struct dev_info* adapter; } ;
struct dev_info {int /*<<< orphan*/  tx_tasklet; int /*<<< orphan*/  rx_tasklet; struct net_device* dev; struct ksz_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  hw_cfg_huge_frame (struct dev_info*,struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_reset (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_set_addr (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_set_desc_base (struct ksz_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksz_init_rx_buffers (struct dev_info*) ; 
 int /*<<< orphan*/  netdev_intr ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  rx_proc_task ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tx_proc_task ; 

__attribute__((used)) static int prepare_hardware(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	int rc = 0;

	/* Remember the network device that requests interrupts. */
	hw_priv->dev = dev;
	rc = request_irq(dev->irq, netdev_intr, IRQF_SHARED, dev->name, dev);
	if (rc)
		return rc;
	tasklet_init(&hw_priv->rx_tasklet, rx_proc_task,
		     (unsigned long) hw_priv);
	tasklet_init(&hw_priv->tx_tasklet, tx_proc_task,
		     (unsigned long) hw_priv);

	hw->promiscuous = 0;
	hw->all_multi = 0;
	hw->multi_list_size = 0;

	hw_reset(hw);

	hw_set_desc_base(hw,
		hw->tx_desc_info.ring_phys, hw->rx_desc_info.ring_phys);
	hw_set_addr(hw);
	hw_cfg_huge_frame(hw_priv, hw);
	ksz_init_rx_buffers(hw_priv);
	return 0;
}