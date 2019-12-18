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
struct dm_kcopyd_throttle {int dummy; } ;
struct dm_kcopyd_client {int sub_job_size; int /*<<< orphan*/  job_pool; int /*<<< orphan*/  kcopyd_wq; int /*<<< orphan*/  nr_jobs; int /*<<< orphan*/  destroyq; int /*<<< orphan*/  io_client; scalar_t__ nr_free_pages; scalar_t__ nr_reserved_pages; int /*<<< orphan*/ * pages; int /*<<< orphan*/  kcopyd_work; struct dm_kcopyd_throttle* throttle; int /*<<< orphan*/  pages_jobs; int /*<<< orphan*/  io_jobs; int /*<<< orphan*/  complete_jobs; int /*<<< orphan*/  callback_jobs; int /*<<< orphan*/  job_lock; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct dm_kcopyd_client* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN_JOBS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SECTOR_SHIFT ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  _job_cache ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_free_pages (struct dm_kcopyd_client*) ; 
 int client_reserve_pages (struct dm_kcopyd_client*,unsigned int) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int dm_get_kcopyd_subjob_size () ; 
 int /*<<< orphan*/  dm_io_client_create () ; 
 int /*<<< orphan*/  do_work ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dm_kcopyd_client*) ; 
 struct dm_kcopyd_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 
 int mempool_init_slab_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct dm_kcopyd_client *dm_kcopyd_client_create(struct dm_kcopyd_throttle *throttle)
{
	int r;
	unsigned reserve_pages;
	struct dm_kcopyd_client *kc;

	kc = kzalloc(sizeof(*kc), GFP_KERNEL);
	if (!kc)
		return ERR_PTR(-ENOMEM);

	spin_lock_init(&kc->job_lock);
	INIT_LIST_HEAD(&kc->callback_jobs);
	INIT_LIST_HEAD(&kc->complete_jobs);
	INIT_LIST_HEAD(&kc->io_jobs);
	INIT_LIST_HEAD(&kc->pages_jobs);
	kc->throttle = throttle;

	r = mempool_init_slab_pool(&kc->job_pool, MIN_JOBS, _job_cache);
	if (r)
		goto bad_slab;

	INIT_WORK(&kc->kcopyd_work, do_work);
	kc->kcopyd_wq = alloc_workqueue("kcopyd", WQ_MEM_RECLAIM, 0);
	if (!kc->kcopyd_wq) {
		r = -ENOMEM;
		goto bad_workqueue;
	}

	kc->sub_job_size = dm_get_kcopyd_subjob_size();
	reserve_pages = DIV_ROUND_UP(kc->sub_job_size << SECTOR_SHIFT, PAGE_SIZE);

	kc->pages = NULL;
	kc->nr_reserved_pages = kc->nr_free_pages = 0;
	r = client_reserve_pages(kc, reserve_pages);
	if (r)
		goto bad_client_pages;

	kc->io_client = dm_io_client_create();
	if (IS_ERR(kc->io_client)) {
		r = PTR_ERR(kc->io_client);
		goto bad_io_client;
	}

	init_waitqueue_head(&kc->destroyq);
	atomic_set(&kc->nr_jobs, 0);

	return kc;

bad_io_client:
	client_free_pages(kc);
bad_client_pages:
	destroy_workqueue(kc->kcopyd_wq);
bad_workqueue:
	mempool_exit(&kc->job_pool);
bad_slab:
	kfree(kc);

	return ERR_PTR(r);
}