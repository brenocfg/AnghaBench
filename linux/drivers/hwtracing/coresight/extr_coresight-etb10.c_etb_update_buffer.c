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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct perf_output_handle {unsigned long size; unsigned long head; } ;
struct etb_drvdata {int buffer_depth; int /*<<< orphan*/  spinlock; scalar_t__ base; } ;
struct cs_buffers {int cur; unsigned long offset; int nr_pages; scalar_t__ snapshot; int /*<<< orphan*/ ** data_pages; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 unsigned long CIRC_CNT (int,int,int) ; 
 int CORESIGHT_BARRIER_PKT_SIZE ; 
 int /*<<< orphan*/  CS_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  CS_UNLOCK (scalar_t__) ; 
 int ETB_FRAME_SIZE_WORDS ; 
 scalar_t__ ETB_RAM_READ_DATA_REG ; 
 scalar_t__ ETB_RAM_READ_POINTER ; 
 scalar_t__ ETB_RAM_WRITE_POINTER ; 
 int ETB_STATUS_RAM_FULL ; 
 scalar_t__ ETB_STATUS_REG ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  PERF_AUX_FLAG_TRUNCATED ; 
 int /*<<< orphan*/  __etb_disable_hw (struct etb_drvdata*) ; 
 int /*<<< orphan*/  __etb_enable_hw (struct etb_drvdata*) ; 
 int atomic_read (int /*<<< orphan*/ ) ; 
 int* barrier_pkt ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,unsigned long) ; 
 struct etb_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_aux_output_flag (struct perf_output_handle*,int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static unsigned long etb_update_buffer(struct coresight_device *csdev,
			      struct perf_output_handle *handle,
			      void *sink_config)
{
	bool lost = false;
	int i, cur;
	u8 *buf_ptr;
	const u32 *barrier;
	u32 read_ptr, write_ptr, capacity;
	u32 status, read_data;
	unsigned long offset, to_read = 0, flags;
	struct cs_buffers *buf = sink_config;
	struct etb_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	if (!buf)
		return 0;

	capacity = drvdata->buffer_depth * ETB_FRAME_SIZE_WORDS;

	spin_lock_irqsave(&drvdata->spinlock, flags);

	/* Don't do anything if another tracer is using this sink */
	if (atomic_read(csdev->refcnt) != 1)
		goto out;

	__etb_disable_hw(drvdata);
	CS_UNLOCK(drvdata->base);

	/* unit is in words, not bytes */
	read_ptr = readl_relaxed(drvdata->base + ETB_RAM_READ_POINTER);
	write_ptr = readl_relaxed(drvdata->base + ETB_RAM_WRITE_POINTER);

	/*
	 * Entries should be aligned to the frame size.  If they are not
	 * go back to the last alignment point to give decoding tools a
	 * chance to fix things.
	 */
	if (write_ptr % ETB_FRAME_SIZE_WORDS) {
		dev_err(&csdev->dev,
			"write_ptr: %lu not aligned to formatter frame size\n",
			(unsigned long)write_ptr);

		write_ptr &= ~(ETB_FRAME_SIZE_WORDS - 1);
		lost = true;
	}

	/*
	 * Get a hold of the status register and see if a wrap around
	 * has occurred.  If so adjust things accordingly.  Otherwise
	 * start at the beginning and go until the write pointer has
	 * been reached.
	 */
	status = readl_relaxed(drvdata->base + ETB_STATUS_REG);
	if (status & ETB_STATUS_RAM_FULL) {
		lost = true;
		to_read = capacity;
		read_ptr = write_ptr;
	} else {
		to_read = CIRC_CNT(write_ptr, read_ptr, drvdata->buffer_depth);
		to_read *= ETB_FRAME_SIZE_WORDS;
	}

	/*
	 * Make sure we don't overwrite data that hasn't been consumed yet.
	 * It is entirely possible that the HW buffer has more data than the
	 * ring buffer can currently handle.  If so adjust the start address
	 * to take only the last traces.
	 *
	 * In snapshot mode we are looking to get the latest traces only and as
	 * such, we don't care about not overwriting data that hasn't been
	 * processed by user space.
	 */
	if (!buf->snapshot && to_read > handle->size) {
		u32 mask = ~(ETB_FRAME_SIZE_WORDS - 1);

		/* The new read pointer must be frame size aligned */
		to_read = handle->size & mask;
		/*
		 * Move the RAM read pointer up, keeping in mind that
		 * everything is in frame size units.
		 */
		read_ptr = (write_ptr + drvdata->buffer_depth) -
					to_read / ETB_FRAME_SIZE_WORDS;
		/* Wrap around if need be*/
		if (read_ptr > (drvdata->buffer_depth - 1))
			read_ptr -= drvdata->buffer_depth;
		/* let the decoder know we've skipped ahead */
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

	/* finally tell HW where we want to start reading from */
	writel_relaxed(read_ptr, drvdata->base + ETB_RAM_READ_POINTER);

	cur = buf->cur;
	offset = buf->offset;
	barrier = barrier_pkt;

	for (i = 0; i < to_read; i += 4) {
		buf_ptr = buf->data_pages[cur] + offset;
		read_data = readl_relaxed(drvdata->base +
					  ETB_RAM_READ_DATA_REG);
		if (lost && i < CORESIGHT_BARRIER_PKT_SIZE) {
			read_data = *barrier;
			barrier++;
		}

		*(u32 *)buf_ptr = read_data;
		buf_ptr += 4;

		offset += 4;
		if (offset >= PAGE_SIZE) {
			offset = 0;
			cur++;
			/* wrap around at the end of the buffer */
			cur &= buf->nr_pages - 1;
		}
	}

	/* reset ETB buffer for next run */
	writel_relaxed(0x0, drvdata->base + ETB_RAM_READ_POINTER);
	writel_relaxed(0x0, drvdata->base + ETB_RAM_WRITE_POINTER);

	/*
	 * In snapshot mode we simply increment the head by the number of byte
	 * that were written.  User space function  cs_etm_find_snapshot() will
	 * figure out how many bytes to get from the AUX buffer based on the
	 * position of the head.
	 */
	if (buf->snapshot)
		handle->head += to_read;

	__etb_enable_hw(drvdata);
	CS_LOCK(drvdata->base);
out:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	return to_read;
}