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
struct tmc_drvdata {scalar_t__ mode; int size; int memwidth; scalar_t__ base; } ;
struct perf_output_handle {int size; } ;
struct cs_buffers {int cur; unsigned long offset; int** data_pages; int nr_pages; int /*<<< orphan*/  data_size; scalar_t__ snapshot; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int CIRC_CNT (int,int,int) ; 
 int /*<<< orphan*/  CS_LOCK (scalar_t__) ; 
 scalar_t__ CS_MODE_PERF ; 
 int /*<<< orphan*/  CS_UNLOCK (scalar_t__) ; 
 int GENMASK (int,int) ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  PERF_AUX_FLAG_TRUNCATED ; 
#define  TMC_MEM_INTF_WIDTH_128BITS 131 
#define  TMC_MEM_INTF_WIDTH_256BITS 130 
#define  TMC_MEM_INTF_WIDTH_32BITS 129 
#define  TMC_MEM_INTF_WIDTH_64BITS 128 
 scalar_t__ TMC_RRD ; 
 scalar_t__ TMC_STS ; 
 int TMC_STS_FULL ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int* barrier_pkt ; 
 struct tmc_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  perf_aux_output_flag (struct perf_output_handle*,int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  tmc_flush_and_stop (struct tmc_drvdata*) ; 
 int tmc_read_rrp (struct tmc_drvdata*) ; 
 int tmc_read_rwp (struct tmc_drvdata*) ; 
 int /*<<< orphan*/  tmc_write_rrp (struct tmc_drvdata*,int) ; 

__attribute__((used)) static void tmc_update_etf_buffer(struct coresight_device *csdev,
				  struct perf_output_handle *handle,
				  void *sink_config)
{
	bool lost = false;
	int i, cur;
	const u32 *barrier;
	u32 *buf_ptr;
	u64 read_ptr, write_ptr;
	u32 status, to_read;
	unsigned long offset;
	struct cs_buffers *buf = sink_config;
	struct tmc_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	if (!buf)
		return;

	/* This shouldn't happen */
	if (WARN_ON_ONCE(drvdata->mode != CS_MODE_PERF))
		return;

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
	 * get the latest trace data.
	 */
	if (to_read > handle->size) {
		u32 mask = 0;

		/*
		 * The value written to RRP must be byte-address aligned to
		 * the width of the trace memory databus _and_ to a frame
		 * boundary (16 byte), whichever is the biggest. For example,
		 * for 32-bit, 64-bit and 128-bit wide trace memory, the four
		 * LSBs must be 0s. For 256-bit wide trace memory, the five
		 * LSBs must be 0s.
		 */
		switch (drvdata->memwidth) {
		case TMC_MEM_INTF_WIDTH_32BITS:
		case TMC_MEM_INTF_WIDTH_64BITS:
		case TMC_MEM_INTF_WIDTH_128BITS:
			mask = GENMASK(31, 5);
			break;
		case TMC_MEM_INTF_WIDTH_256BITS:
			mask = GENMASK(31, 6);
			break;
		}

		/*
		 * Make sure the new size is aligned in accordance with the
		 * requirement explained above.
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

	if (lost)
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
	 * In snapshot mode all we have to do is communicate to
	 * perf_aux_output_end() the address of the current head.  In full
	 * trace mode the same function expects a size to move rb->aux_head
	 * forward.
	 */
	if (buf->snapshot)
		local_set(&buf->data_size, (cur * PAGE_SIZE) + offset);
	else
		local_add(to_read, &buf->data_size);

	CS_LOCK(drvdata->base);
}