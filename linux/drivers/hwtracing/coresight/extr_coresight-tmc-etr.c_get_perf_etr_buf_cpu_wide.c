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
struct tmc_drvdata {int /*<<< orphan*/  idr_mutex; int /*<<< orphan*/  idr; } ;
struct perf_event {int /*<<< orphan*/  owner; } ;
struct etr_buf {int /*<<< orphan*/  refcount; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 struct etr_buf* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct etr_buf*) ; 
 struct etr_buf* alloc_etr_buf (struct tmc_drvdata*,struct perf_event*,int,void**,int) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct etr_buf*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct etr_buf* idr_find (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ task_pid_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmc_free_etr_buf (struct etr_buf*) ; 

__attribute__((used)) static struct etr_buf *
get_perf_etr_buf_cpu_wide(struct tmc_drvdata *drvdata,
			  struct perf_event *event, int nr_pages,
			  void **pages, bool snapshot)
{
	int ret;
	pid_t pid = task_pid_nr(event->owner);
	struct etr_buf *etr_buf;

retry:
	/*
	 * An etr_perf_buffer is associated with an event and holds a reference
	 * to the AUX ring buffer that was created for that event.  In CPU-wide
	 * N:1 mode multiple events (one per CPU), each with its own AUX ring
	 * buffer, share a sink.  As such an etr_perf_buffer is created for each
	 * event but a single etr_buf associated with the ETR is shared between
	 * them.  The last event in a trace session will copy the content of the
	 * etr_buf to its AUX ring buffer.  Ring buffer associated to other
	 * events are simply not used an freed as events are destoyed.  We still
	 * need to allocate a ring buffer for each event since we don't know
	 * which event will be last.
	 */

	/*
	 * The first thing to do here is check if an etr_buf has already been
	 * allocated for this session.  If so it is shared with this event,
	 * otherwise it is created.
	 */
	mutex_lock(&drvdata->idr_mutex);
	etr_buf = idr_find(&drvdata->idr, pid);
	if (etr_buf) {
		refcount_inc(&etr_buf->refcount);
		mutex_unlock(&drvdata->idr_mutex);
		return etr_buf;
	}

	/* If we made it here no buffer has been allocated, do so now. */
	mutex_unlock(&drvdata->idr_mutex);

	etr_buf = alloc_etr_buf(drvdata, event, nr_pages, pages, snapshot);
	if (IS_ERR(etr_buf))
		return etr_buf;

	/* Now that we have a buffer, add it to the IDR. */
	mutex_lock(&drvdata->idr_mutex);
	ret = idr_alloc(&drvdata->idr, etr_buf, pid, pid + 1, GFP_KERNEL);
	mutex_unlock(&drvdata->idr_mutex);

	/* Another event with this session ID has allocated this buffer. */
	if (ret == -ENOSPC) {
		tmc_free_etr_buf(etr_buf);
		goto retry;
	}

	/* The IDR can't allocate room for a new session, abandon ship. */
	if (ret == -ENOMEM) {
		tmc_free_etr_buf(etr_buf);
		return ERR_PTR(ret);
	}


	return etr_buf;
}