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
struct drm_client_buffer {void* vaddr; int /*<<< orphan*/  gem; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 void* drm_gem_vmap (int /*<<< orphan*/ ) ; 

void *drm_client_buffer_vmap(struct drm_client_buffer *buffer)
{
	void *vaddr;

	if (buffer->vaddr)
		return buffer->vaddr;

	/*
	 * FIXME: The dependency on GEM here isn't required, we could
	 * convert the driver handle to a dma-buf instead and use the
	 * backend-agnostic dma-buf vmap support instead. This would
	 * require that the handle2fd prime ioctl is reworked to pull the
	 * fd_install step out of the driver backend hooks, to make that
	 * final step optional for internal users.
	 */
	vaddr = drm_gem_vmap(buffer->gem);
	if (IS_ERR(vaddr))
		return vaddr;

	buffer->vaddr = vaddr;

	return vaddr;
}