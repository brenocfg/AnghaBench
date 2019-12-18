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
struct ufx_data {scalar_t__ fb_count; int /*<<< orphan*/  kref; int /*<<< orphan*/  free_framebuffer_work; scalar_t__ virtualized; } ;
struct fb_info {int /*<<< orphan*/  node; TYPE_1__* fbops; int /*<<< orphan*/ * fbdefio; struct ufx_data* par; } ;
struct TYPE_2__ {int /*<<< orphan*/  fb_mmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  fb_deferred_io_cleanup (struct fb_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufx_free ; 
 int /*<<< orphan*/  ufx_ops_mmap ; 

__attribute__((used)) static int ufx_ops_release(struct fb_info *info, int user)
{
	struct ufx_data *dev = info->par;

	dev->fb_count--;

	/* We can't free fb_info here - fbmem will touch it when we return */
	if (dev->virtualized && (dev->fb_count == 0))
		schedule_delayed_work(&dev->free_framebuffer_work, HZ);

	if ((dev->fb_count == 0) && (info->fbdefio)) {
		fb_deferred_io_cleanup(info);
		kfree(info->fbdefio);
		info->fbdefio = NULL;
		info->fbops->fb_mmap = ufx_ops_mmap;
	}

	pr_debug("released /dev/fb%d user=%d count=%d",
		  info->node, user, dev->fb_count);

	kref_put(&dev->kref, ufx_free);

	return 0;
}