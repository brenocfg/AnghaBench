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
typedef  void* u32 ;
struct drm_mode_create_dumb {int bpp; int /*<<< orphan*/  handle; int /*<<< orphan*/  pitch; void* height; void* width; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {TYPE_1__* driver; } ;
struct drm_client_dev {int /*<<< orphan*/  file; struct drm_device* dev; } ;
struct drm_client_buffer {void* vaddr; struct drm_gem_object* gem; int /*<<< orphan*/  pitch; int /*<<< orphan*/  handle; struct drm_client_dev* client; } ;
struct TYPE_2__ {void* (* gem_prime_vmap ) (struct drm_gem_object*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 struct drm_client_buffer* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_client_buffer_delete (struct drm_client_buffer*) ; 
 int drm_format_plane_cpp (void*,int /*<<< orphan*/ ) ; 
 struct drm_gem_object* drm_gem_object_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_mode_create_dumb (struct drm_device*,struct drm_mode_create_dumb*,int /*<<< orphan*/ ) ; 
 struct drm_client_buffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* stub1 (struct drm_gem_object*) ; 

__attribute__((used)) static struct drm_client_buffer *
drm_client_buffer_create(struct drm_client_dev *client, u32 width, u32 height, u32 format)
{
	struct drm_mode_create_dumb dumb_args = { };
	struct drm_device *dev = client->dev;
	struct drm_client_buffer *buffer;
	struct drm_gem_object *obj;
	void *vaddr;
	int ret;

	buffer = kzalloc(sizeof(*buffer), GFP_KERNEL);
	if (!buffer)
		return ERR_PTR(-ENOMEM);

	buffer->client = client;

	dumb_args.width = width;
	dumb_args.height = height;
	dumb_args.bpp = drm_format_plane_cpp(format, 0) * 8;
	ret = drm_mode_create_dumb(dev, &dumb_args, client->file);
	if (ret)
		goto err_delete;

	buffer->handle = dumb_args.handle;
	buffer->pitch = dumb_args.pitch;

	obj = drm_gem_object_lookup(client->file, dumb_args.handle);
	if (!obj)  {
		ret = -ENOENT;
		goto err_delete;
	}

	buffer->gem = obj;

	/*
	 * FIXME: The dependency on GEM here isn't required, we could
	 * convert the driver handle to a dma-buf instead and use the
	 * backend-agnostic dma-buf vmap support instead. This would
	 * require that the handle2fd prime ioctl is reworked to pull the
	 * fd_install step out of the driver backend hooks, to make that
	 * final step optional for internal users.
	 */
	vaddr = dev->driver->gem_prime_vmap(obj);
	if (!vaddr) {
		ret = -ENOMEM;
		goto err_delete;
	}

	buffer->vaddr = vaddr;

	return buffer;

err_delete:
	drm_client_buffer_delete(buffer);

	return ERR_PTR(ret);
}