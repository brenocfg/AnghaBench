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
struct sync_file {int /*<<< orphan*/  file; int /*<<< orphan*/  fence; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 struct dma_fence* dma_fence_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 struct sync_file* sync_file_fdget (int) ; 

struct dma_fence *sync_file_get_fence(int fd)
{
	struct sync_file *sync_file;
	struct dma_fence *fence;

	sync_file = sync_file_fdget(fd);
	if (!sync_file)
		return NULL;

	fence = dma_fence_get(sync_file->fence);
	fput(sync_file->file);

	return fence;
}