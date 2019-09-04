#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  cb; int /*<<< orphan*/  list; } ;
struct TYPE_10__ {TYPE_4__ w; } ;
struct TYPE_8__ {int /*<<< orphan*/  cb; int /*<<< orphan*/  list; } ;
struct TYPE_7__ {int /*<<< orphan*/  cb; int /*<<< orphan*/  list; } ;
struct TYPE_6__ {int /*<<< orphan*/  in_use; } ;
struct drbd_device {void* local_max_bio_size; void* peer_max_bio_size; int /*<<< orphan*/  resync_wenr; int /*<<< orphan*/  seq_wait; int /*<<< orphan*/  al_wait; int /*<<< orphan*/  ee_wait; int /*<<< orphan*/  state_wait; int /*<<< orphan*/  misc_wait; int /*<<< orphan*/  request_timer; int /*<<< orphan*/  start_resync_timer; int /*<<< orphan*/  md_sync_timer; int /*<<< orphan*/  resync_timer; TYPE_5__ bm_io_work; TYPE_3__ unplug_work; TYPE_2__ resync_work; int /*<<< orphan*/ * pending_completion; int /*<<< orphan*/ * pending_master_completion; int /*<<< orphan*/  resync_reads; int /*<<< orphan*/  net_ee; int /*<<< orphan*/  read_ee; int /*<<< orphan*/  done_ee; int /*<<< orphan*/  sync_ee; int /*<<< orphan*/  active_ee; int /*<<< orphan*/  peer_seq_lock; int /*<<< orphan*/  al_lock; int /*<<< orphan*/  own_state_mutex; int /*<<< orphan*/ * state_mutex; TYPE_1__ md_io; int /*<<< orphan*/  ap_in_flight; int /*<<< orphan*/  rs_sect_ev; int /*<<< orphan*/  rs_sect_in; int /*<<< orphan*/  pp_in_use_by_net; int /*<<< orphan*/  local_cnt; int /*<<< orphan*/  unacked_cnt; int /*<<< orphan*/  rs_pending_cnt; int /*<<< orphan*/  ap_pending_cnt; int /*<<< orphan*/  ap_actlog_cnt; int /*<<< orphan*/  ap_bio_cnt; } ;

/* Variables and functions */
 void* DRBD_MAX_BIO_SIZE_SAFE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LC_FREE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_set_defaults (struct drbd_device*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_sync_timer_fn ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_timer_fn ; 
 int /*<<< orphan*/  resync_timer_fn ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_resync_timer_fn ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_bitmap_io ; 
 int /*<<< orphan*/  w_resync_timer ; 
 int /*<<< orphan*/  w_send_write_hint ; 

void drbd_init_set_defaults(struct drbd_device *device)
{
	/* the memset(,0,) did most of this.
	 * note: only assignments, no allocation in here */

	drbd_set_defaults(device);

	atomic_set(&device->ap_bio_cnt, 0);
	atomic_set(&device->ap_actlog_cnt, 0);
	atomic_set(&device->ap_pending_cnt, 0);
	atomic_set(&device->rs_pending_cnt, 0);
	atomic_set(&device->unacked_cnt, 0);
	atomic_set(&device->local_cnt, 0);
	atomic_set(&device->pp_in_use_by_net, 0);
	atomic_set(&device->rs_sect_in, 0);
	atomic_set(&device->rs_sect_ev, 0);
	atomic_set(&device->ap_in_flight, 0);
	atomic_set(&device->md_io.in_use, 0);

	mutex_init(&device->own_state_mutex);
	device->state_mutex = &device->own_state_mutex;

	spin_lock_init(&device->al_lock);
	spin_lock_init(&device->peer_seq_lock);

	INIT_LIST_HEAD(&device->active_ee);
	INIT_LIST_HEAD(&device->sync_ee);
	INIT_LIST_HEAD(&device->done_ee);
	INIT_LIST_HEAD(&device->read_ee);
	INIT_LIST_HEAD(&device->net_ee);
	INIT_LIST_HEAD(&device->resync_reads);
	INIT_LIST_HEAD(&device->resync_work.list);
	INIT_LIST_HEAD(&device->unplug_work.list);
	INIT_LIST_HEAD(&device->bm_io_work.w.list);
	INIT_LIST_HEAD(&device->pending_master_completion[0]);
	INIT_LIST_HEAD(&device->pending_master_completion[1]);
	INIT_LIST_HEAD(&device->pending_completion[0]);
	INIT_LIST_HEAD(&device->pending_completion[1]);

	device->resync_work.cb  = w_resync_timer;
	device->unplug_work.cb  = w_send_write_hint;
	device->bm_io_work.w.cb = w_bitmap_io;

	timer_setup(&device->resync_timer, resync_timer_fn, 0);
	timer_setup(&device->md_sync_timer, md_sync_timer_fn, 0);
	timer_setup(&device->start_resync_timer, start_resync_timer_fn, 0);
	timer_setup(&device->request_timer, request_timer_fn, 0);

	init_waitqueue_head(&device->misc_wait);
	init_waitqueue_head(&device->state_wait);
	init_waitqueue_head(&device->ee_wait);
	init_waitqueue_head(&device->al_wait);
	init_waitqueue_head(&device->seq_wait);

	device->resync_wenr = LC_FREE;
	device->peer_max_bio_size = DRBD_MAX_BIO_SIZE_SAFE;
	device->local_max_bio_size = DRBD_MAX_BIO_SIZE_SAFE;
}