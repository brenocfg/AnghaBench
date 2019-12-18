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
struct vm_area_struct {int dummy; } ;
struct fb_info {struct au1200fb_device* par; } ;
struct au1200fb_device {int /*<<< orphan*/  fb_len; int /*<<< orphan*/  fb_phys; int /*<<< orphan*/  fb_mem; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int dma_mmap_attrs (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int au1200fb_fb_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	struct au1200fb_device *fbdev = info->par;

	return dma_mmap_attrs(fbdev->dev, vma, fbdev->fb_mem, fbdev->fb_phys,
			fbdev->fb_len, 0);
}