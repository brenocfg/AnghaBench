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
struct net_device {int dummy; } ;
struct list_head {int dummy; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  list; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  IS_ERR (struct net_device*) ; 
 int /*<<< orphan*/  ib_set_client_data (struct ib_device*,int /*<<< orphan*/ *,struct list_head*) ; 
 struct net_device* ipoib_add_port (char*,struct ib_device*,int) ; 
 int /*<<< orphan*/  ipoib_client ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct list_head*) ; 
 struct list_head* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int rdma_end_port (struct ib_device*) ; 
 int /*<<< orphan*/  rdma_protocol_ib (struct ib_device*,int) ; 
 int rdma_start_port (struct ib_device*) ; 

__attribute__((used)) static void ipoib_add_one(struct ib_device *device)
{
	struct list_head *dev_list;
	struct net_device *dev;
	struct ipoib_dev_priv *priv;
	int p;
	int count = 0;

	dev_list = kmalloc(sizeof(*dev_list), GFP_KERNEL);
	if (!dev_list)
		return;

	INIT_LIST_HEAD(dev_list);

	for (p = rdma_start_port(device); p <= rdma_end_port(device); ++p) {
		if (!rdma_protocol_ib(device, p))
			continue;
		dev = ipoib_add_port("ib%d", device, p);
		if (!IS_ERR(dev)) {
			priv = ipoib_priv(dev);
			list_add_tail(&priv->list, dev_list);
			count++;
		}
	}

	if (!count) {
		kfree(dev_list);
		return;
	}

	ib_set_client_data(device, &ipoib_client, dev_list);
}