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
struct ufx_data {int dummy; } ;
struct TYPE_4__ {int smem_len; int line_length; unsigned long smem_start; } ;
struct TYPE_3__ {int yres; } ;
struct fb_info {unsigned char* screen_base; int /*<<< orphan*/  flags; TYPE_2__ fix; TYPE_1__ var; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_ALIGN (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  smscufx_info_flags ; 
 int /*<<< orphan*/  vfree (unsigned char*) ; 
 unsigned char* vmalloc (int) ; 

__attribute__((used)) static int ufx_realloc_framebuffer(struct ufx_data *dev, struct fb_info *info)
{
	int old_len = info->fix.smem_len;
	int new_len;
	unsigned char *old_fb = info->screen_base;
	unsigned char *new_fb;

	pr_debug("Reallocating framebuffer. Addresses will change!");

	new_len = info->fix.line_length * info->var.yres;

	if (PAGE_ALIGN(new_len) > old_len) {
		/*
		 * Alloc system memory for virtual framebuffer
		 */
		new_fb = vmalloc(new_len);
		if (!new_fb)
			return -ENOMEM;

		if (info->screen_base) {
			memcpy(new_fb, old_fb, old_len);
			vfree(info->screen_base);
		}

		info->screen_base = new_fb;
		info->fix.smem_len = PAGE_ALIGN(new_len);
		info->fix.smem_start = (unsigned long) new_fb;
		info->flags = smscufx_info_flags;
	}
	return 0;
}