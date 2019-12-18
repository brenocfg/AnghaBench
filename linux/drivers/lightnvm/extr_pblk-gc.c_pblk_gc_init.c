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
struct pblk_gc {int gc_enabled; void* gc_ts; void* gc_writer_ts; void* gc_reader_ts; void* gc_line_reader_wq; int /*<<< orphan*/  r_list; int /*<<< orphan*/  w_list; int /*<<< orphan*/  gc_sem; int /*<<< orphan*/  r_lock; int /*<<< orphan*/  w_lock; int /*<<< orphan*/  lock; void* gc_reader_wq; int /*<<< orphan*/  pipeline_gc; int /*<<< orphan*/  read_inflight_gc; scalar_t__ w_entries; scalar_t__ gc_forced; scalar_t__ gc_active; int /*<<< orphan*/  gc_timer; } ;
struct pblk {struct pblk_gc gc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GC_TIME_MSECS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (void*) ; 
 int PBLK_GC_MAX_READERS ; 
 int /*<<< orphan*/  PBLK_GC_RQ_QD ; 
 int PTR_ERR (void*) ; 
 int WQ_MEM_RECLAIM ; 
 int WQ_UNBOUND ; 
 void* alloc_workqueue (char*,int,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (void*) ; 
 scalar_t__ jiffies ; 
 void* kthread_create (int /*<<< orphan*/ ,struct pblk*,char*) ; 
 int /*<<< orphan*/  kthread_stop (void*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*) ; 
 int /*<<< orphan*/  pblk_gc_reader_ts ; 
 int /*<<< orphan*/  pblk_gc_timer ; 
 int /*<<< orphan*/  pblk_gc_ts ; 
 int /*<<< orphan*/  pblk_gc_writer_ts ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pblk_gc_init(struct pblk *pblk)
{
	struct pblk_gc *gc = &pblk->gc;
	int ret;

	gc->gc_ts = kthread_create(pblk_gc_ts, pblk, "pblk-gc-ts");
	if (IS_ERR(gc->gc_ts)) {
		pblk_err(pblk, "could not allocate GC main kthread\n");
		return PTR_ERR(gc->gc_ts);
	}

	gc->gc_writer_ts = kthread_create(pblk_gc_writer_ts, pblk,
							"pblk-gc-writer-ts");
	if (IS_ERR(gc->gc_writer_ts)) {
		pblk_err(pblk, "could not allocate GC writer kthread\n");
		ret = PTR_ERR(gc->gc_writer_ts);
		goto fail_free_main_kthread;
	}

	gc->gc_reader_ts = kthread_create(pblk_gc_reader_ts, pblk,
							"pblk-gc-reader-ts");
	if (IS_ERR(gc->gc_reader_ts)) {
		pblk_err(pblk, "could not allocate GC reader kthread\n");
		ret = PTR_ERR(gc->gc_reader_ts);
		goto fail_free_writer_kthread;
	}

	timer_setup(&gc->gc_timer, pblk_gc_timer, 0);
	mod_timer(&gc->gc_timer, jiffies + msecs_to_jiffies(GC_TIME_MSECS));

	gc->gc_active = 0;
	gc->gc_forced = 0;
	gc->gc_enabled = 1;
	gc->w_entries = 0;
	atomic_set(&gc->read_inflight_gc, 0);
	atomic_set(&gc->pipeline_gc, 0);

	/* Workqueue that reads valid sectors from a line and submit them to the
	 * GC writer to be recycled.
	 */
	gc->gc_line_reader_wq = alloc_workqueue("pblk-gc-line-reader-wq",
			WQ_MEM_RECLAIM | WQ_UNBOUND, PBLK_GC_MAX_READERS);
	if (!gc->gc_line_reader_wq) {
		pblk_err(pblk, "could not allocate GC line reader workqueue\n");
		ret = -ENOMEM;
		goto fail_free_reader_kthread;
	}

	/* Workqueue that prepare lines for GC */
	gc->gc_reader_wq = alloc_workqueue("pblk-gc-line_wq",
					WQ_MEM_RECLAIM | WQ_UNBOUND, 1);
	if (!gc->gc_reader_wq) {
		pblk_err(pblk, "could not allocate GC reader workqueue\n");
		ret = -ENOMEM;
		goto fail_free_reader_line_wq;
	}

	spin_lock_init(&gc->lock);
	spin_lock_init(&gc->w_lock);
	spin_lock_init(&gc->r_lock);

	sema_init(&gc->gc_sem, PBLK_GC_RQ_QD);

	INIT_LIST_HEAD(&gc->w_list);
	INIT_LIST_HEAD(&gc->r_list);

	return 0;

fail_free_reader_line_wq:
	destroy_workqueue(gc->gc_line_reader_wq);
fail_free_reader_kthread:
	kthread_stop(gc->gc_reader_ts);
fail_free_writer_kthread:
	kthread_stop(gc->gc_writer_ts);
fail_free_main_kthread:
	kthread_stop(gc->gc_ts);

	return ret;
}