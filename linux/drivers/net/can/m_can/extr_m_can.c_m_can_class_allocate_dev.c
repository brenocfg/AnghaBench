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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct m_can_classdev {struct device* dev; struct net_device* net; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  mram_config_vals ;

/* Variables and functions */
 int MRAM_CFG_LEN ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,struct device*) ; 
 struct net_device* alloc_candev (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_fwnode (struct device*) ; 
 int fwnode_property_read_u32_array (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  m_can_of_parse_mram (struct m_can_classdev*,int /*<<< orphan*/ *) ; 
 struct m_can_classdev* netdev_priv (struct net_device*) ; 

struct m_can_classdev *m_can_class_allocate_dev(struct device *dev)
{
	struct m_can_classdev *class_dev = NULL;
	u32 mram_config_vals[MRAM_CFG_LEN];
	struct net_device *net_dev;
	u32 tx_fifo_size;
	int ret;

	ret = fwnode_property_read_u32_array(dev_fwnode(dev),
					     "bosch,mram-cfg",
					     mram_config_vals,
					     sizeof(mram_config_vals) / 4);
	if (ret) {
		dev_err(dev, "Could not get Message RAM configuration.");
		goto out;
	}

	/* Get TX FIFO size
	 * Defines the total amount of echo buffers for loopback
	 */
	tx_fifo_size = mram_config_vals[7];

	/* allocate the m_can device */
	net_dev = alloc_candev(sizeof(*class_dev), tx_fifo_size);
	if (!net_dev) {
		dev_err(dev, "Failed to allocate CAN device");
		goto out;
	}

	class_dev = netdev_priv(net_dev);
	if (!class_dev) {
		dev_err(dev, "Failed to init netdev cdevate");
		goto out;
	}

	class_dev->net = net_dev;
	class_dev->dev = dev;
	SET_NETDEV_DEV(net_dev, dev);

	m_can_of_parse_mram(class_dev, mram_config_vals);
out:
	return class_dev;
}