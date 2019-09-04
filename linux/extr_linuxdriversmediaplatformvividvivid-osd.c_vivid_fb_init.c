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
struct vivid_dev {int video_buffer_size; int /*<<< orphan*/  fb_info; int /*<<< orphan*/ * video_vbase; int /*<<< orphan*/  video_pbase; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_DMA32 ; 
 int GFP_KERNEL ; 
 int MAX_OSD_HEIGHT ; 
 int MAX_OSD_WIDTH ; 
 int /*<<< orphan*/ * kzalloc (int,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ register_framebuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vivid_clear_fb (struct vivid_dev*) ; 
 int vivid_fb_init_vidmode (struct vivid_dev*) ; 
 int /*<<< orphan*/  vivid_fb_release_buffers (struct vivid_dev*) ; 
 int /*<<< orphan*/  vivid_fb_set_par (int /*<<< orphan*/ *) ; 

int vivid_fb_init(struct vivid_dev *dev)
{
	int ret;

	dev->video_buffer_size = MAX_OSD_HEIGHT * MAX_OSD_WIDTH * 2;
	dev->video_vbase = kzalloc(dev->video_buffer_size, GFP_KERNEL | GFP_DMA32);
	if (dev->video_vbase == NULL)
		return -ENOMEM;
	dev->video_pbase = virt_to_phys(dev->video_vbase);

	pr_info("Framebuffer at 0x%lx, mapped to 0x%p, size %dk\n",
			dev->video_pbase, dev->video_vbase,
			dev->video_buffer_size / 1024);

	/* Set the startup video mode information */
	ret = vivid_fb_init_vidmode(dev);
	if (ret) {
		vivid_fb_release_buffers(dev);
		return ret;
	}

	vivid_clear_fb(dev);

	/* Register the framebuffer */
	if (register_framebuffer(&dev->fb_info) < 0) {
		vivid_fb_release_buffers(dev);
		return -EINVAL;
	}

	/* Set the card to the requested mode */
	vivid_fb_set_par(&dev->fb_info);
	return 0;

}