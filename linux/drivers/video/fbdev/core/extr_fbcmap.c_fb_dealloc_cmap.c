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
struct fb_cmap {scalar_t__ len; int /*<<< orphan*/ * transp; int /*<<< orphan*/ * blue; int /*<<< orphan*/ * green; int /*<<< orphan*/ * red; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void fb_dealloc_cmap(struct fb_cmap *cmap)
{
	kfree(cmap->red);
	kfree(cmap->green);
	kfree(cmap->blue);
	kfree(cmap->transp);

	cmap->red = cmap->green = cmap->blue = cmap->transp = NULL;
	cmap->len = 0;
}