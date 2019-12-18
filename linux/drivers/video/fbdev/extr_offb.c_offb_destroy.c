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
struct fb_info {int /*<<< orphan*/  cmap; TYPE_2__* apertures; scalar_t__ screen_base; } ;
struct TYPE_4__ {TYPE_1__* ranges; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void offb_destroy(struct fb_info *info)
{
	if (info->screen_base)
		iounmap(info->screen_base);
	release_mem_region(info->apertures->ranges[0].base, info->apertures->ranges[0].size);
	fb_dealloc_cmap(&info->cmap);
	framebuffer_release(info);
}