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
struct virtio_gpu_fbdev {int /*<<< orphan*/  helper; int /*<<< orphan*/  work; struct virtio_gpu_device* vgdev; } ;
struct virtio_gpu_device {int /*<<< orphan*/  ddev; struct virtio_gpu_fbdev* vgfbdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIRTIO_GPUFB_CONN_LIMIT ; 
 int drm_fb_helper_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fb_helper_initial_config (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_fb_helper_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_helper_single_add_all_connectors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct virtio_gpu_fbdev*) ; 
 struct virtio_gpu_fbdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_gpu_fb_dirty_work ; 
 int /*<<< orphan*/  virtio_gpu_fb_helper_funcs ; 

int virtio_gpu_fbdev_init(struct virtio_gpu_device *vgdev)
{
	struct virtio_gpu_fbdev *vgfbdev;
	int bpp_sel = 32; /* TODO: parameter from somewhere? */
	int ret;

	vgfbdev = kzalloc(sizeof(struct virtio_gpu_fbdev), GFP_KERNEL);
	if (!vgfbdev)
		return -ENOMEM;

	vgfbdev->vgdev = vgdev;
	vgdev->vgfbdev = vgfbdev;
	INIT_DELAYED_WORK(&vgfbdev->work, virtio_gpu_fb_dirty_work);

	drm_fb_helper_prepare(vgdev->ddev, &vgfbdev->helper,
			      &virtio_gpu_fb_helper_funcs);
	ret = drm_fb_helper_init(vgdev->ddev, &vgfbdev->helper,
				 VIRTIO_GPUFB_CONN_LIMIT);
	if (ret) {
		kfree(vgfbdev);
		return ret;
	}

	drm_fb_helper_single_add_all_connectors(&vgfbdev->helper);
	drm_fb_helper_initial_config(&vgfbdev->helper, bpp_sel);
	return 0;
}