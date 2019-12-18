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
typedef  int /*<<< orphan*/  u16 ;
struct fb_cmap {int len; scalar_t__ start; int /*<<< orphan*/ * transp; void* blue; void* green; void* red; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  __GFP_NOWARN ; 
 int fb_copy_cmap (int /*<<< orphan*/ ,struct fb_cmap*) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (struct fb_cmap*) ; 
 int /*<<< orphan*/  fb_default_cmap (int) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 

int fb_alloc_cmap_gfp(struct fb_cmap *cmap, int len, int transp, gfp_t flags)
{
	int size = len * sizeof(u16);
	int ret = -ENOMEM;

	flags |= __GFP_NOWARN;

	if (cmap->len != len) {
		fb_dealloc_cmap(cmap);
		if (!len)
			return 0;

		cmap->red = kmalloc(size, flags);
		if (!cmap->red)
			goto fail;
		cmap->green = kmalloc(size, flags);
		if (!cmap->green)
			goto fail;
		cmap->blue = kmalloc(size, flags);
		if (!cmap->blue)
			goto fail;
		if (transp) {
			cmap->transp = kmalloc(size, flags);
			if (!cmap->transp)
				goto fail;
		} else {
			cmap->transp = NULL;
		}
	}
	cmap->start = 0;
	cmap->len = len;
	ret = fb_copy_cmap(fb_default_cmap(len), cmap);
	if (ret)
		goto fail;
	return 0;

fail:
	fb_dealloc_cmap(cmap);
	return ret;
}