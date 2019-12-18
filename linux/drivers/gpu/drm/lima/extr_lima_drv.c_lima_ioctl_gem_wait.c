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
struct drm_lima_gem_wait {int op; int /*<<< orphan*/  timeout_ns; int /*<<< orphan*/  handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int LIMA_GEM_WAIT_READ ; 
 int LIMA_GEM_WAIT_WRITE ; 
 int lima_gem_wait (struct drm_file*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lima_ioctl_gem_wait(struct drm_device *dev, void *data, struct drm_file *file)
{
	struct drm_lima_gem_wait *args = data;

	if (args->op & ~(LIMA_GEM_WAIT_READ|LIMA_GEM_WAIT_WRITE))
		return -EINVAL;

	return lima_gem_wait(file, args->handle, args->op, args->timeout_ns);
}