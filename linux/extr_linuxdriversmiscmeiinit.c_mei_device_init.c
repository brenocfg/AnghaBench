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
struct mei_hw_ops {int dummy; } ;
struct mei_device {struct device* dev; struct mei_hw_ops const* ops; int /*<<< orphan*/  pg_event; int /*<<< orphan*/  host_clients_map; scalar_t__ open_handle_count; int /*<<< orphan*/  bus_rescan_work; int /*<<< orphan*/  reset_work; int /*<<< orphan*/  timer_work; int /*<<< orphan*/  tx_queue_limit; int /*<<< orphan*/  ctrl_rd_list; int /*<<< orphan*/  ctrl_wr_list; int /*<<< orphan*/  write_waiting_list; int /*<<< orphan*/  write_list; scalar_t__ reset_count; int /*<<< orphan*/  dev_state; int /*<<< orphan*/  wait_hbm_start; int /*<<< orphan*/  wait_pg; int /*<<< orphan*/  wait_hw_ready; int /*<<< orphan*/  cl_bus_lock; int /*<<< orphan*/  me_clients_rwsem; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  me_clients; int /*<<< orphan*/  device_list; int /*<<< orphan*/  file_list; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEI_CLIENTS_MAX ; 
 int /*<<< orphan*/  MEI_DEV_INITIALIZING ; 
 int /*<<< orphan*/  MEI_PG_EVENT_IDLE ; 
 int /*<<< orphan*/  MEI_TX_QUEUE_LIMIT_DEFAULT ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mei_cl_bus_rescan_work ; 
 int /*<<< orphan*/  mei_reset_work ; 
 int /*<<< orphan*/  mei_timer ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void mei_device_init(struct mei_device *dev,
		     struct device *device,
		     const struct mei_hw_ops *hw_ops)
{
	/* setup our list array */
	INIT_LIST_HEAD(&dev->file_list);
	INIT_LIST_HEAD(&dev->device_list);
	INIT_LIST_HEAD(&dev->me_clients);
	mutex_init(&dev->device_lock);
	init_rwsem(&dev->me_clients_rwsem);
	mutex_init(&dev->cl_bus_lock);
	init_waitqueue_head(&dev->wait_hw_ready);
	init_waitqueue_head(&dev->wait_pg);
	init_waitqueue_head(&dev->wait_hbm_start);
	dev->dev_state = MEI_DEV_INITIALIZING;
	dev->reset_count = 0;

	INIT_LIST_HEAD(&dev->write_list);
	INIT_LIST_HEAD(&dev->write_waiting_list);
	INIT_LIST_HEAD(&dev->ctrl_wr_list);
	INIT_LIST_HEAD(&dev->ctrl_rd_list);
	dev->tx_queue_limit = MEI_TX_QUEUE_LIMIT_DEFAULT;

	INIT_DELAYED_WORK(&dev->timer_work, mei_timer);
	INIT_WORK(&dev->reset_work, mei_reset_work);
	INIT_WORK(&dev->bus_rescan_work, mei_cl_bus_rescan_work);

	bitmap_zero(dev->host_clients_map, MEI_CLIENTS_MAX);
	dev->open_handle_count = 0;

	/*
	 * Reserving the first client ID
	 * 0: Reserved for MEI Bus Message communications
	 */
	bitmap_set(dev->host_clients_map, 0, 1);

	dev->pg_event = MEI_PG_EVENT_IDLE;
	dev->ops      = hw_ops;
	dev->dev      = device;
}