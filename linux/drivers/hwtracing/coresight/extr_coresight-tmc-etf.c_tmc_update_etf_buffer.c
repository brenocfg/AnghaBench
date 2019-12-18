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
typedef  int u64 ;
typedef  int u32 ;
struct tmc_drvdata {scalar_t__ mode; unsigned long size; int /*<<< orphan*/  spinlock; scalar_t__ base; } ;
struct perf_output_handle {unsigned long size; unsigned long head; } ;
struct cs_buffers {int cur; unsigned long offset; int** data_pages; int nr_pages; scalar_t__ snapshot; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {int /*<<< orphan*/  refcnt; TYPE_1__ dev; } ;

/* Variables and functions */
 unsigned long CIRC_CNT (int,int,unsigned long) ; 
 int /*<<< orphan*/  CS_LOCK (scalar_t__) ; 
 scalar_t__ CS_MODE_PERF ; 
 int /*<<< orphan*/  CS_UNLOCK (scalar_t__) ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  PERF_AUX_FLAG_TRUNCATED ; 
 scalar_t__ TMC_RRD ; 
 scalar_t__ TMC_STS ; 
 int TMC_STS_FULL ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int atomic_read (int /*<<< orphan*/ ) ; 
 int* barrier_pkt ; 
 struct tmc_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_aux_output_flag (struct perf_output_handle*,int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tmc_flush_and_stop (struct tmc_drvdata*) ; 
 int tmc_get_memwidth_mask (struct tmc_drvdata*) ; 
 int tmc_read_rrp (struct tmc_drvdata*) ; 
 int tmc_read_rwp (struct tmc_drvdata*) ; 
 int /*<<< orphan*/  tmc_write_rrp (struct tmc_drvdata*,int) ; 

__attribute__((used)) static unsigned long tmc_update_etf_buffer(struct coresight_device *csdev,
				  struct perf_output_handle *handle,
				  void *sink_config)
{
	bool lost = false;
	int i, cur;
	const u32 *barrier;
	u32 *buf_ptr;
	u64 read_ptr, write_ptr;
	u32 status;
	unsigned long offset, to_read = 0, flags;
	struct cs_buffers *buf = sink_config;
	struct tmc_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	if (!buf)
		return 0;

	/* This shouldn't happen */
	if (WARN_ON_ONCE(drvdata->mode != CS_MODE_PERF))
		return 0;

	spin_lock_irqsave(&drvdata->spinlock, flags);

	/* Don't do anything if another tracer is using this sink */
	if (atomic_read(csdev->refcnt) != 1)
		goto out;

	CS_UNLOCK(drvdata->base);

	tmc_flush_and_stop(drvdata);

	read_ptr = tmc_read_rrp(drvdata);
	write_ptr = tmc_read_rwp(drvdata);

	/*
	 * Get a hold of the status register and see if a wrap around
	 * has occurred.  If so adjust things accordingly.
	 */
	status = readl_relaxed(drvdata->base + TMC_STS);
	if (status & TMC_STS_FULL) {
		lost = true;
		to_read = drvdata->size;
	} else {
		to_read = CIRC_CNT(write_ptr, read_ptr, drvdata->size);
	}

	/*
	 * The TMC RAM buffer may be bigger than the space available in the
	 * perf ring buffer (handle->size).  If so advance the RRP so that we
	 * get the latest trace data.  In snapshot mode none of that matters
	 * since we are expected to clobber stale data in favour of the latest
	 * traces.
	 */
	if (!buf->snapshot && to_read > handle->size) {
		u32 mask = tmc_get_memwidth_mask(drvdata);

		/*
		 * Make sure the new size is aligned in accordance with the
		 * requirement explained in function tmc_get_memwidth_mask().
		 */
		to_read = handle->size & mask;
		/* Move the RAM read pointer up */
		read_ptr = (write_ptr + drvdata->size) - to_read;
		/* Make sure we are still within our limits */
		if (read_ptr > (drvdata->size - 1))
			read_ptr -= drvdata->size;
		/* Tell the HW */
		tmc_write_rrp(drvdata, read_ptr);
		lost = true;
	}

	/*
	 * Don't set the TRUNCATED flag in snapshot mode because 1) the
	 * captured buffer is expected to be truncated and 2) a full buffer
	 * prevents the event from being re-enabled by the perf core,
	 * resulting in stale data being send to user space.
	 */
	if (!buf->snapshot && lost)
		perf_aux_output_flag(handle, PERF_AUX_FLAG_TRUNCATED);

	cur = buf->cur;
	offset = buf->offset;
	barrier = barrier_pkt;

	/* for every byte to read */
	for (i = 0; i < to_read; i += 4) {
		buf_ptr = buf->data_pages[cur] + offset;
		*buf_ptr = readl_relaxed(drvdata->base + TMC_RRD);

		if (lost && *barrier) {
			*buf_ptr = *barrier;
			barrier++;
		}

		offset += 4;
		if (offset >= PAGE_SIZE) {
			offset = 0;
			cur++;
			/* wrap around at the end of the buffer */
			cur &= buf->nr_pages - 1;
		}
	}

	/*
	 * In snapshot mode we simply increment the head by the number of byte
	 * that were written.  User space function  cs_etm_find_snapshot() will
	 * figure out how many bytes to get from the AUX buffer based on the
	 * position of the head.
	 */
	if (buf->snapshot)
		handle->head += to_read;

	CS_LOCK(drvdata->base);
out:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	return to_read;
}