#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int handle; } ;
struct TYPE_3__ {int what; int /*<<< orphan*/  fence; } ;
union drm_amdgpu_fence_to_handle {TYPE_2__ out; TYPE_1__ in; } ;
struct sync_file {int /*<<< orphan*/  file; } ;
struct drm_syncobj {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct dma_fence {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
#define  AMDGPU_FENCE_TO_HANDLE_GET_SYNCOBJ 130 
#define  AMDGPU_FENCE_TO_HANDLE_GET_SYNCOBJ_FD 129 
#define  AMDGPU_FENCE_TO_HANDLE_GET_SYNC_FILE_FD 128 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct dma_fence*) ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int PTR_ERR (struct dma_fence*) ; 
 struct dma_fence* amdgpu_cs_get_fence (struct amdgpu_device*,struct drm_file*,int /*<<< orphan*/ *) ; 
 struct dma_fence* dma_fence_get_stub () ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int drm_syncobj_create (struct drm_syncobj**,int /*<<< orphan*/ ,struct dma_fence*) ; 
 int drm_syncobj_get_fd (struct drm_syncobj*,int*) ; 
 int drm_syncobj_get_handle (struct drm_file*,struct drm_syncobj*,int*) ; 
 int /*<<< orphan*/  drm_syncobj_put (struct drm_syncobj*) ; 
 int /*<<< orphan*/  fd_install (int,int /*<<< orphan*/ ) ; 
 int get_unused_fd_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 
 struct sync_file* sync_file_create (struct dma_fence*) ; 

int amdgpu_cs_fence_to_handle_ioctl(struct drm_device *dev, void *data,
				    struct drm_file *filp)
{
	struct amdgpu_device *adev = dev->dev_private;
	union drm_amdgpu_fence_to_handle *info = data;
	struct dma_fence *fence;
	struct drm_syncobj *syncobj;
	struct sync_file *sync_file;
	int fd, r;

	fence = amdgpu_cs_get_fence(adev, filp, &info->in.fence);
	if (IS_ERR(fence))
		return PTR_ERR(fence);

	if (!fence)
		fence = dma_fence_get_stub();

	switch (info->in.what) {
	case AMDGPU_FENCE_TO_HANDLE_GET_SYNCOBJ:
		r = drm_syncobj_create(&syncobj, 0, fence);
		dma_fence_put(fence);
		if (r)
			return r;
		r = drm_syncobj_get_handle(filp, syncobj, &info->out.handle);
		drm_syncobj_put(syncobj);
		return r;

	case AMDGPU_FENCE_TO_HANDLE_GET_SYNCOBJ_FD:
		r = drm_syncobj_create(&syncobj, 0, fence);
		dma_fence_put(fence);
		if (r)
			return r;
		r = drm_syncobj_get_fd(syncobj, (int*)&info->out.handle);
		drm_syncobj_put(syncobj);
		return r;

	case AMDGPU_FENCE_TO_HANDLE_GET_SYNC_FILE_FD:
		fd = get_unused_fd_flags(O_CLOEXEC);
		if (fd < 0) {
			dma_fence_put(fence);
			return fd;
		}

		sync_file = sync_file_create(fence);
		dma_fence_put(fence);
		if (!sync_file) {
			put_unused_fd(fd);
			return -ENOMEM;
		}

		fd_install(fd, sync_file->file);
		info->out.handle = fd;
		return 0;

	default:
		return -EINVAL;
	}
}