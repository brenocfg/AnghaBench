#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  seq_print; } ;
struct TYPE_8__ {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  work; int /*<<< orphan*/  list; } ;
struct TYPE_7__ {struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int /*<<< orphan*/  stat_read_buf_num; int /*<<< orphan*/  dma_parms; struct ccw_device* ccw_device; TYPE_3__ service_level; int /*<<< orphan*/  abort_lock; int /*<<< orphan*/  erp_lock; int /*<<< orphan*/  erp_running_head; int /*<<< orphan*/  erp_ready_head; int /*<<< orphan*/  erp_done_wqh; int /*<<< orphan*/  erp_ready_wq; TYPE_2__ events; int /*<<< orphan*/  port_list; int /*<<< orphan*/  port_list_lock; int /*<<< orphan*/  req_list; TYPE_1__ erp_action; int /*<<< orphan*/  next_port_scan; int /*<<< orphan*/  ns_up_work; int /*<<< orphan*/  scan_work; int /*<<< orphan*/  stat_work; int /*<<< orphan*/  ref; } ;
struct TYPE_10__ {int /*<<< orphan*/ * dma_parms; int /*<<< orphan*/  kobj; } ;
struct ccw_device {TYPE_4__ dev; int /*<<< orphan*/ * handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct zfcp_adapter* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSF_STATUS_READS_RECOM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _zfcp_status_read_scheduler ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_4__*,struct zfcp_adapter*) ; 
 int /*<<< orphan*/  get_device (TYPE_4__*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct zfcp_adapter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_4__*) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_adapter_unregister (struct zfcp_adapter*) ; 
 scalar_t__ zfcp_allocate_low_mem_buffers (struct zfcp_adapter*) ; 
 scalar_t__ zfcp_dbf_adapter_register (struct zfcp_adapter*) ; 
 scalar_t__ zfcp_erp_thread_setup (struct zfcp_adapter*) ; 
 scalar_t__ zfcp_fc_gs_setup (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_fc_post_event ; 
 int /*<<< orphan*/  zfcp_fc_scan_ports ; 
 int /*<<< orphan*/  zfcp_fc_sym_name_update ; 
 int /*<<< orphan*/  zfcp_print_sl ; 
 scalar_t__ zfcp_qdio_setup (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_reqlist_alloc () ; 
 int /*<<< orphan*/  zfcp_scsi_adapter_register (struct zfcp_adapter*) ; 
 scalar_t__ zfcp_setup_adapter_work_queue (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_sysfs_adapter_attrs ; 

struct zfcp_adapter *zfcp_adapter_enqueue(struct ccw_device *ccw_device)
{
	struct zfcp_adapter *adapter;

	if (!get_device(&ccw_device->dev))
		return ERR_PTR(-ENODEV);

	adapter = kzalloc(sizeof(struct zfcp_adapter), GFP_KERNEL);
	if (!adapter) {
		put_device(&ccw_device->dev);
		return ERR_PTR(-ENOMEM);
	}

	kref_init(&adapter->ref);

	ccw_device->handler = NULL;
	adapter->ccw_device = ccw_device;

	INIT_WORK(&adapter->stat_work, _zfcp_status_read_scheduler);
	INIT_DELAYED_WORK(&adapter->scan_work, zfcp_fc_scan_ports);
	INIT_WORK(&adapter->ns_up_work, zfcp_fc_sym_name_update);

	adapter->next_port_scan = jiffies;

	adapter->erp_action.adapter = adapter;

	if (zfcp_qdio_setup(adapter))
		goto failed;

	if (zfcp_allocate_low_mem_buffers(adapter))
		goto failed;

	adapter->req_list = zfcp_reqlist_alloc();
	if (!adapter->req_list)
		goto failed;

	if (zfcp_dbf_adapter_register(adapter))
		goto failed;

	if (zfcp_setup_adapter_work_queue(adapter))
		goto failed;

	if (zfcp_fc_gs_setup(adapter))
		goto failed;

	rwlock_init(&adapter->port_list_lock);
	INIT_LIST_HEAD(&adapter->port_list);

	INIT_LIST_HEAD(&adapter->events.list);
	INIT_WORK(&adapter->events.work, zfcp_fc_post_event);
	spin_lock_init(&adapter->events.list_lock);

	init_waitqueue_head(&adapter->erp_ready_wq);
	init_waitqueue_head(&adapter->erp_done_wqh);

	INIT_LIST_HEAD(&adapter->erp_ready_head);
	INIT_LIST_HEAD(&adapter->erp_running_head);

	rwlock_init(&adapter->erp_lock);
	rwlock_init(&adapter->abort_lock);

	if (zfcp_erp_thread_setup(adapter))
		goto failed;

	adapter->service_level.seq_print = zfcp_print_sl;

	dev_set_drvdata(&ccw_device->dev, adapter);

	if (sysfs_create_group(&ccw_device->dev.kobj,
			       &zfcp_sysfs_adapter_attrs))
		goto failed;

	/* report size limit per scatter-gather segment */
	adapter->ccw_device->dev.dma_parms = &adapter->dma_parms;

	adapter->stat_read_buf_num = FSF_STATUS_READS_RECOM;

	if (!zfcp_scsi_adapter_register(adapter))
		return adapter;

failed:
	zfcp_adapter_unregister(adapter);
	return ERR_PTR(-ENOMEM);
}