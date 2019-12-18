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
struct sync_file {int /*<<< orphan*/  file; } ;
struct drm_file {int dummy; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int drm_syncobj_find_fence (struct drm_file*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_fence**) ; 
 int /*<<< orphan*/  fd_install (int,int /*<<< orphan*/ ) ; 
 int get_unused_fd_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 
 struct sync_file* sync_file_create (struct dma_fence*) ; 

__attribute__((used)) static int drm_syncobj_export_sync_file(struct drm_file *file_private,
					int handle, int *p_fd)
{
	int ret;
	struct dma_fence *fence;
	struct sync_file *sync_file;
	int fd = get_unused_fd_flags(O_CLOEXEC);

	if (fd < 0)
		return fd;

	ret = drm_syncobj_find_fence(file_private, handle, 0, 0, &fence);
	if (ret)
		goto err_put_fd;

	sync_file = sync_file_create(fence);

	dma_fence_put(fence);

	if (!sync_file) {
		ret = -EINVAL;
		goto err_put_fd;
	}

	fd_install(fd, sync_file->file);

	*p_fd = fd;
	return 0;
err_put_fd:
	put_unused_fd(fd);
	return ret;
}