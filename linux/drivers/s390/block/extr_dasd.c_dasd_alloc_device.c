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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct dasd_device {TYPE_1__ profile; int /*<<< orphan*/  state_mutex; void* target; void* state; int /*<<< orphan*/  requeue_requests; int /*<<< orphan*/  reload_device; int /*<<< orphan*/  restore_device; int /*<<< orphan*/  kick_work; int /*<<< orphan*/  timer; int /*<<< orphan*/  ccw_queue; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  tasklet_scheduled; int /*<<< orphan*/  mem_lock; void* ese_mem; int /*<<< orphan*/  ese_chunks; void* erp_mem; int /*<<< orphan*/  erp_chunks; void* ccw_mem; int /*<<< orphan*/  ccw_chunks; } ;

/* Variables and functions */
 void* DASD_STATE_NEW ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dasd_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 scalar_t__ __get_free_pages (int,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_device_tasklet ; 
 int /*<<< orphan*/  dasd_device_timeout ; 
 int /*<<< orphan*/  dasd_init_chunklist (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  do_kick_device ; 
 int /*<<< orphan*/  do_reload_device ; 
 int /*<<< orphan*/  do_requeue_requests ; 
 int /*<<< orphan*/  do_restore_device ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 scalar_t__ get_zeroed_page (int) ; 
 int /*<<< orphan*/  kfree (struct dasd_device*) ; 
 struct dasd_device* kzalloc (int,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct dasd_device *dasd_alloc_device(void)
{
	struct dasd_device *device;

	device = kzalloc(sizeof(struct dasd_device), GFP_ATOMIC);
	if (!device)
		return ERR_PTR(-ENOMEM);

	/* Get two pages for normal block device operations. */
	device->ccw_mem = (void *) __get_free_pages(GFP_ATOMIC | GFP_DMA, 1);
	if (!device->ccw_mem) {
		kfree(device);
		return ERR_PTR(-ENOMEM);
	}
	/* Get one page for error recovery. */
	device->erp_mem = (void *) get_zeroed_page(GFP_ATOMIC | GFP_DMA);
	if (!device->erp_mem) {
		free_pages((unsigned long) device->ccw_mem, 1);
		kfree(device);
		return ERR_PTR(-ENOMEM);
	}
	/* Get two pages for ese format. */
	device->ese_mem = (void *)__get_free_pages(GFP_ATOMIC | GFP_DMA, 1);
	if (!device->ese_mem) {
		free_page((unsigned long) device->erp_mem);
		free_pages((unsigned long) device->ccw_mem, 1);
		kfree(device);
		return ERR_PTR(-ENOMEM);
	}

	dasd_init_chunklist(&device->ccw_chunks, device->ccw_mem, PAGE_SIZE*2);
	dasd_init_chunklist(&device->erp_chunks, device->erp_mem, PAGE_SIZE);
	dasd_init_chunklist(&device->ese_chunks, device->ese_mem, PAGE_SIZE * 2);
	spin_lock_init(&device->mem_lock);
	atomic_set(&device->tasklet_scheduled, 0);
	tasklet_init(&device->tasklet, dasd_device_tasklet,
		     (unsigned long) device);
	INIT_LIST_HEAD(&device->ccw_queue);
	timer_setup(&device->timer, dasd_device_timeout, 0);
	INIT_WORK(&device->kick_work, do_kick_device);
	INIT_WORK(&device->restore_device, do_restore_device);
	INIT_WORK(&device->reload_device, do_reload_device);
	INIT_WORK(&device->requeue_requests, do_requeue_requests);
	device->state = DASD_STATE_NEW;
	device->target = DASD_STATE_NEW;
	mutex_init(&device->state_mutex);
	spin_lock_init(&device->profile.lock);
	return device;
}