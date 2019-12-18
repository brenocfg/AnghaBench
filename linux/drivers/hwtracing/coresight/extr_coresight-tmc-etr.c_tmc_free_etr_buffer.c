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
struct etr_perf_buffer {struct etr_buf* etr_buf; int /*<<< orphan*/  pid; struct tmc_drvdata* drvdata; } ;
struct etr_buf {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct etr_buf* idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct etr_perf_buffer*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmc_free_etr_buf (struct etr_buf*) ; 

__attribute__((used)) static void tmc_free_etr_buffer(void *config)
{
	struct etr_perf_buffer *etr_perf = config;
	struct tmc_drvdata *drvdata = etr_perf->drvdata;
	struct etr_buf *buf, *etr_buf = etr_perf->etr_buf;

	if (!etr_buf)
		goto free_etr_perf_buffer;

	mutex_lock(&drvdata->idr_mutex);
	/* If we are not the last one to use the buffer, don't touch it. */
	if (!refcount_dec_and_test(&etr_buf->refcount)) {
		mutex_unlock(&drvdata->idr_mutex);
		goto free_etr_perf_buffer;
	}

	/* We are the last one, remove from the IDR and free the buffer. */
	buf = idr_remove(&drvdata->idr, etr_perf->pid);
	mutex_unlock(&drvdata->idr_mutex);

	/*
	 * Something went very wrong if the buffer associated with this ID
	 * is not the same in the IDR.  Leak to avoid use after free.
	 */
	if (buf && WARN_ON(buf != etr_buf))
		goto free_etr_perf_buffer;

	tmc_free_etr_buf(etr_perf->etr_buf);

free_etr_perf_buffer:
	kfree(etr_perf);
}