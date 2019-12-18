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
typedef  int u32 ;
struct TYPE_3__ {int line_length; int smem_len; int /*<<< orphan*/  smem_start; } ;
struct TYPE_4__ {int yres_virtual; } ;
struct fb_info {int screen_size; TYPE_1__ fix; int /*<<< orphan*/  mm_lock; void* screen_base; int /*<<< orphan*/  dev; TYPE_2__ var; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA ; 
 int __GFP_ZERO ; 
 void* alloc_pages_exact (int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

__attribute__((used)) static int map_video_memory(struct fb_info *info)
{
	u32 smem_len = info->fix.line_length * info->var.yres_virtual;
	void *p;

	p = alloc_pages_exact(smem_len, GFP_DMA | __GFP_ZERO);
	if (!p) {
		dev_err(info->dev, "unable to allocate fb memory\n");
		return -ENOMEM;
	}
	mutex_lock(&info->mm_lock);
	info->screen_base = p;
	info->fix.smem_start = virt_to_phys(info->screen_base);
	info->fix.smem_len = smem_len;
	mutex_unlock(&info->mm_lock);
	info->screen_size = info->fix.smem_len;

	return 0;
}