#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int dummy; } ;
struct fb_info {struct drm_fb_helper* par; } ;
struct drm_fb_helper {TYPE_3__* buffer; TYPE_2__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  gem; } ;
struct TYPE_5__ {TYPE_1__* driver; } ;
struct TYPE_4__ {int (* gem_prime_mmap ) (int /*<<< orphan*/ ,struct vm_area_struct*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int stub1 (int /*<<< orphan*/ ,struct vm_area_struct*) ; 

__attribute__((used)) static int drm_fbdev_fb_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	struct drm_fb_helper *fb_helper = info->par;

	if (fb_helper->dev->driver->gem_prime_mmap)
		return fb_helper->dev->driver->gem_prime_mmap(fb_helper->buffer->gem, vma);
	else
		return -ENODEV;
}