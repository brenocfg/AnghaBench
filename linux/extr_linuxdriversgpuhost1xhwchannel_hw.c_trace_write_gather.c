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
typedef  int u32 ;
struct host1x_cdma {int dummy; } ;
struct host1x_bo {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 scalar_t__ TRACE_MAX_LENGTH ; 
 TYPE_1__* cdma_to_channel (struct host1x_cdma*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 void* host1x_bo_mmap (struct host1x_bo*) ; 
 int /*<<< orphan*/  host1x_bo_munmap (struct host1x_bo*,void*) ; 
 scalar_t__ host1x_debug_trace_cmdbuf ; 
 int min (int,scalar_t__) ; 
 int /*<<< orphan*/  trace_host1x_cdma_push_gather (int /*<<< orphan*/ ,struct host1x_bo*,int,int,void*) ; 

__attribute__((used)) static void trace_write_gather(struct host1x_cdma *cdma, struct host1x_bo *bo,
			       u32 offset, u32 words)
{
	struct device *dev = cdma_to_channel(cdma)->dev;
	void *mem = NULL;

	if (host1x_debug_trace_cmdbuf)
		mem = host1x_bo_mmap(bo);

	if (mem) {
		u32 i;
		/*
		 * Write in batches of 128 as there seems to be a limit
		 * of how much you can output to ftrace at once.
		 */
		for (i = 0; i < words; i += TRACE_MAX_LENGTH) {
			u32 num_words = min(words - i, TRACE_MAX_LENGTH);

			offset += i * sizeof(u32);

			trace_host1x_cdma_push_gather(dev_name(dev), bo,
						      num_words, offset,
						      mem);
		}

		host1x_bo_munmap(bo, mem);
	}
}