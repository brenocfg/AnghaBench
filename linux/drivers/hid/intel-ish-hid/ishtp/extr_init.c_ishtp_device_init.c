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
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct ishtp_device {TYPE_1__ read_list; int /*<<< orphan*/  host_clients_map; scalar_t__ open_handle_count; int /*<<< orphan*/  bh_hbm_work; int /*<<< orphan*/  fw_clients_lock; int /*<<< orphan*/  cl_list_lock; int /*<<< orphan*/  device_list_lock; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  read_list_spinlock; int /*<<< orphan*/  wait_hbm_recvd_msg; int /*<<< orphan*/  rd_msg_spinlock; scalar_t__ rd_msg_fifo_tail; scalar_t__ rd_msg_fifo_head; int /*<<< orphan*/  device_list; int /*<<< orphan*/  cl_list; int /*<<< orphan*/  dev_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISHTP_CLIENTS_MAX ; 
 int /*<<< orphan*/  ISHTP_DEV_INITIALIZING ; 
 int /*<<< orphan*/  bh_hbm_work_fn ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void ishtp_device_init(struct ishtp_device *dev)
{
	dev->dev_state = ISHTP_DEV_INITIALIZING;
	INIT_LIST_HEAD(&dev->cl_list);
	INIT_LIST_HEAD(&dev->device_list);
	dev->rd_msg_fifo_head = 0;
	dev->rd_msg_fifo_tail = 0;
	spin_lock_init(&dev->rd_msg_spinlock);

	init_waitqueue_head(&dev->wait_hbm_recvd_msg);
	spin_lock_init(&dev->read_list_spinlock);
	spin_lock_init(&dev->device_lock);
	spin_lock_init(&dev->device_list_lock);
	spin_lock_init(&dev->cl_list_lock);
	spin_lock_init(&dev->fw_clients_lock);
	INIT_WORK(&dev->bh_hbm_work, bh_hbm_work_fn);

	bitmap_zero(dev->host_clients_map, ISHTP_CLIENTS_MAX);
	dev->open_handle_count = 0;

	/*
	 * Reserving client ID 0 for ISHTP Bus Message communications
	 */
	bitmap_set(dev->host_clients_map, 0, 1);

	INIT_LIST_HEAD(&dev->read_list.list);

}