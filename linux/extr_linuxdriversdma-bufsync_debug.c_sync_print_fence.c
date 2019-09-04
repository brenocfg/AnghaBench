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
typedef  int /*<<< orphan*/  value ;
struct timespec64 {int /*<<< orphan*/  tv_nsec; scalar_t__ tv_sec; } ;
struct sync_timeline {char* name; } ;
struct seq_file {int dummy; } ;
struct dma_fence {TYPE_1__* ops; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_2__ {int /*<<< orphan*/  (* timeline_value_str ) (struct dma_fence*,char*,int) ;int /*<<< orphan*/  (* fence_value_str ) (struct dma_fence*,char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FENCE_FLAG_TIMESTAMP_BIT ; 
 int dma_fence_get_status_locked (struct dma_fence*) ; 
 struct sync_timeline* dma_fence_parent (struct dma_fence*) ; 
 struct timespec64 ktime_to_timespec64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 (struct dma_fence*,char*,int) ; 
 int /*<<< orphan*/  stub2 (struct dma_fence*,char*,int) ; 
 int /*<<< orphan*/  sync_status_str (int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sync_print_fence(struct seq_file *s,
			     struct dma_fence *fence, bool show)
{
	struct sync_timeline *parent = dma_fence_parent(fence);
	int status;

	status = dma_fence_get_status_locked(fence);

	seq_printf(s, "  %s%sfence %s",
		   show ? parent->name : "",
		   show ? "_" : "",
		   sync_status_str(status));

	if (test_bit(DMA_FENCE_FLAG_TIMESTAMP_BIT, &fence->flags)) {
		struct timespec64 ts64 =
			ktime_to_timespec64(fence->timestamp);

		seq_printf(s, "@%lld.%09ld", (s64)ts64.tv_sec, ts64.tv_nsec);
	}

	if (fence->ops->timeline_value_str &&
		fence->ops->fence_value_str) {
		char value[64];
		bool success;

		fence->ops->fence_value_str(fence, value, sizeof(value));
		success = strlen(value);

		if (success) {
			seq_printf(s, ": %s", value);

			fence->ops->timeline_value_str(fence, value,
						       sizeof(value));

			if (strlen(value))
				seq_printf(s, " / %s", value);
		}
	}

	seq_putc(s, '\n');
}