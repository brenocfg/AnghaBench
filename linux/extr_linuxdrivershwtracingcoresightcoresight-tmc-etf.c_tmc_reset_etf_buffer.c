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
struct perf_output_handle {void* head; } ;
struct cs_buffers {int nr_pages; int /*<<< orphan*/  data_size; scalar_t__ snapshot; } ;
struct coresight_device {int dummy; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 void* local_xchg (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned long tmc_reset_etf_buffer(struct coresight_device *csdev,
					  struct perf_output_handle *handle,
					  void *sink_config)
{
	long size = 0;
	struct cs_buffers *buf = sink_config;

	if (buf) {
		/*
		 * In snapshot mode ->data_size holds the new address of the
		 * ring buffer's head.  The size itself is the whole address
		 * range since we want the latest information.
		 */
		if (buf->snapshot)
			handle->head = local_xchg(&buf->data_size,
						  buf->nr_pages << PAGE_SHIFT);
		/*
		 * Tell the tracer PMU how much we got in this run and if
		 * something went wrong along the way.  Nobody else can use
		 * this cs_buffers instance until we are done.  As such
		 * resetting parameters here and squaring off with the ring
		 * buffer API in the tracer PMU is fine.
		 */
		size = local_xchg(&buf->data_size, 0);
	}

	return size;
}