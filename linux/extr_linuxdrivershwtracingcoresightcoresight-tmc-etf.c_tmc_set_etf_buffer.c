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
struct perf_output_handle {int head; } ;
struct cs_buffers {int nr_pages; unsigned long cur; unsigned long offset; int /*<<< orphan*/  data_size; } ;
struct coresight_device {int dummy; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  local_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tmc_set_etf_buffer(struct coresight_device *csdev,
			      struct perf_output_handle *handle,
			      void *sink_config)
{
	int ret = 0;
	unsigned long head;
	struct cs_buffers *buf = sink_config;

	/* wrap head around to the amount of space we have */
	head = handle->head & ((buf->nr_pages << PAGE_SHIFT) - 1);

	/* find the page to write to */
	buf->cur = head / PAGE_SIZE;

	/* and offset within that page */
	buf->offset = head % PAGE_SIZE;

	local_set(&buf->data_size, 0);

	return ret;
}