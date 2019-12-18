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
struct lock_class_key {int dummy; } ;
struct iwl_trans_ops {int /*<<< orphan*/  wait_tx_queues_empty; int /*<<< orphan*/  wait_txq_empty; } ;
struct iwl_trans {int num_rx_queues; int /*<<< orphan*/  dev_cmd_pool; int /*<<< orphan*/  dev_cmd_pool_name; struct device* dev; struct iwl_trans_ops const* ops; int /*<<< orphan*/  sync_cmd_lockdep_map; } ;
struct iwl_device_cmd {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 char* dev_name (struct device*) ; 
 struct iwl_trans* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_create (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_init_map (int /*<<< orphan*/ *,char*,struct lock_class_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

struct iwl_trans *iwl_trans_alloc(unsigned int priv_size,
				  struct device *dev,
				  const struct iwl_trans_ops *ops)
{
	struct iwl_trans *trans;
#ifdef CONFIG_LOCKDEP
	static struct lock_class_key __key;
#endif

	trans = devm_kzalloc(dev, sizeof(*trans) + priv_size, GFP_KERNEL);
	if (!trans)
		return NULL;

#ifdef CONFIG_LOCKDEP
	lockdep_init_map(&trans->sync_cmd_lockdep_map, "sync_cmd_lockdep_map",
			 &__key, 0);
#endif

	trans->dev = dev;
	trans->ops = ops;
	trans->num_rx_queues = 1;

	snprintf(trans->dev_cmd_pool_name, sizeof(trans->dev_cmd_pool_name),
		 "iwl_cmd_pool:%s", dev_name(trans->dev));
	trans->dev_cmd_pool =
		kmem_cache_create(trans->dev_cmd_pool_name,
				  sizeof(struct iwl_device_cmd),
				  sizeof(void *),
				  SLAB_HWCACHE_ALIGN,
				  NULL);
	if (!trans->dev_cmd_pool)
		return NULL;

	WARN_ON(!ops->wait_txq_empty && !ops->wait_tx_queues_empty);

	return trans;
}