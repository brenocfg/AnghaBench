#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {struct net_device* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  list; } ;
struct efx_nic {int rx_prefix_size; int rx_ip_align; int rx_packet_hash_offset; int rx_packet_ts_offset; int num_mac_stats; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  workqueue_name; TYPE_4__* type; int /*<<< orphan*/  interrupt_mode; TYPE_3__* msi_context; int /*<<< orphan*/ * channel; int /*<<< orphan*/  flush_wq; int /*<<< orphan*/  mac_work; TYPE_2__ mdio; int /*<<< orphan*/ * phy_op; int /*<<< orphan*/  rps_hash_table; int /*<<< orphan*/  rps_hash_lock; int /*<<< orphan*/  rps_mutex; int /*<<< orphan*/  mac_lock; int /*<<< orphan*/  vi_stride; int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  rss_lock; TYPE_1__ rss_context; struct net_device* net_dev; int /*<<< orphan*/  name; int /*<<< orphan*/  state; int /*<<< orphan*/  msg_enable; struct pci_dev* pci_dev; int /*<<< orphan*/  selftest_work; int /*<<< orphan*/  monitor_work; int /*<<< orphan*/  reset_work; int /*<<< orphan*/  mtd_list; int /*<<< orphan*/  biu_lock; int /*<<< orphan*/  secondary_list; int /*<<< orphan*/  node; } ;
struct TYPE_8__ {int rx_prefix_size; int rx_hash_offset; int rx_ts_offset; scalar_t__ max_interrupt_mode; scalar_t__ min_interrupt_mode; } ;
struct TYPE_7__ {int index; struct efx_nic* efx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  EFX_ARFS_HASH_TABLE_SIZE ; 
 int /*<<< orphan*/  EFX_DEFAULT_VI_STRIDE ; 
 int EFX_MAX_CHANNELS ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MC_CMD_MAC_GENERATION_END ; 
 int MC_CMD_MAC_NSTATS ; 
 int NET_IP_ALIGN ; 
 int /*<<< orphan*/  STATE_UNINIT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  efx_alloc_channel (struct efx_nic*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_dummy_phy_operations ; 
 int /*<<< orphan*/  efx_fini_struct (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mac_work ; 
 int /*<<< orphan*/  efx_monitor ; 
 int /*<<< orphan*/  efx_reset_work ; 
 int /*<<< orphan*/  efx_selftest_async_work ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interrupt_mode ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 char* pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int efx_init_struct(struct efx_nic *efx,
			   struct pci_dev *pci_dev, struct net_device *net_dev)
{
	int rc = -ENOMEM, i;

	/* Initialise common structures */
	INIT_LIST_HEAD(&efx->node);
	INIT_LIST_HEAD(&efx->secondary_list);
	spin_lock_init(&efx->biu_lock);
#ifdef CONFIG_SFC_MTD
	INIT_LIST_HEAD(&efx->mtd_list);
#endif
	INIT_WORK(&efx->reset_work, efx_reset_work);
	INIT_DELAYED_WORK(&efx->monitor_work, efx_monitor);
	INIT_DELAYED_WORK(&efx->selftest_work, efx_selftest_async_work);
	efx->pci_dev = pci_dev;
	efx->msg_enable = debug;
	efx->state = STATE_UNINIT;
	strlcpy(efx->name, pci_name(pci_dev), sizeof(efx->name));

	efx->net_dev = net_dev;
	efx->rx_prefix_size = efx->type->rx_prefix_size;
	efx->rx_ip_align =
		NET_IP_ALIGN ? (efx->rx_prefix_size + NET_IP_ALIGN) % 4 : 0;
	efx->rx_packet_hash_offset =
		efx->type->rx_hash_offset - efx->type->rx_prefix_size;
	efx->rx_packet_ts_offset =
		efx->type->rx_ts_offset - efx->type->rx_prefix_size;
	INIT_LIST_HEAD(&efx->rss_context.list);
	mutex_init(&efx->rss_lock);
	spin_lock_init(&efx->stats_lock);
	efx->vi_stride = EFX_DEFAULT_VI_STRIDE;
	efx->num_mac_stats = MC_CMD_MAC_NSTATS;
	BUILD_BUG_ON(MC_CMD_MAC_NSTATS - 1 != MC_CMD_MAC_GENERATION_END);
	mutex_init(&efx->mac_lock);
#ifdef CONFIG_RFS_ACCEL
	mutex_init(&efx->rps_mutex);
	spin_lock_init(&efx->rps_hash_lock);
	/* Failure to allocate is not fatal, but may degrade ARFS performance */
	efx->rps_hash_table = kcalloc(EFX_ARFS_HASH_TABLE_SIZE,
				      sizeof(*efx->rps_hash_table), GFP_KERNEL);
#endif
	efx->phy_op = &efx_dummy_phy_operations;
	efx->mdio.dev = net_dev;
	INIT_WORK(&efx->mac_work, efx_mac_work);
	init_waitqueue_head(&efx->flush_wq);

	for (i = 0; i < EFX_MAX_CHANNELS; i++) {
		efx->channel[i] = efx_alloc_channel(efx, i, NULL);
		if (!efx->channel[i])
			goto fail;
		efx->msi_context[i].efx = efx;
		efx->msi_context[i].index = i;
	}

	/* Higher numbered interrupt modes are less capable! */
	if (WARN_ON_ONCE(efx->type->max_interrupt_mode >
			 efx->type->min_interrupt_mode)) {
		rc = -EIO;
		goto fail;
	}
	efx->interrupt_mode = max(efx->type->max_interrupt_mode,
				  interrupt_mode);
	efx->interrupt_mode = min(efx->type->min_interrupt_mode,
				  interrupt_mode);

	/* Would be good to use the net_dev name, but we're too early */
	snprintf(efx->workqueue_name, sizeof(efx->workqueue_name), "sfc%s",
		 pci_name(pci_dev));
	efx->workqueue = create_singlethread_workqueue(efx->workqueue_name);
	if (!efx->workqueue)
		goto fail;

	return 0;

fail:
	efx_fini_struct(efx);
	return rc;
}