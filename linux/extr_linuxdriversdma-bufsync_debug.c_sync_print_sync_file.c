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
struct sync_file {int /*<<< orphan*/  fence; } ;
struct seq_file {int dummy; } ;
struct dma_fence_array {int num_fences; int /*<<< orphan*/ * fences; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_get_status (int /*<<< orphan*/ ) ; 
 scalar_t__ dma_fence_is_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,struct sync_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_file_get_name (struct sync_file*,char*,int) ; 
 int /*<<< orphan*/  sync_print_fence (struct seq_file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sync_status_str (int /*<<< orphan*/ ) ; 
 struct dma_fence_array* to_dma_fence_array (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sync_print_sync_file(struct seq_file *s,
				  struct sync_file *sync_file)
{
	char buf[128];
	int i;

	seq_printf(s, "[%p] %s: %s\n", sync_file,
		   sync_file_get_name(sync_file, buf, sizeof(buf)),
		   sync_status_str(dma_fence_get_status(sync_file->fence)));

	if (dma_fence_is_array(sync_file->fence)) {
		struct dma_fence_array *array = to_dma_fence_array(sync_file->fence);

		for (i = 0; i < array->num_fences; ++i)
			sync_print_fence(s, array->fences[i], true);
	} else {
		sync_print_fence(s, sync_file->fence, true);
	}
}