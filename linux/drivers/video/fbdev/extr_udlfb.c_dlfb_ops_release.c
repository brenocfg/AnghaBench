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
struct fb_info {int /*<<< orphan*/  dev; TYPE_1__* fbops; int /*<<< orphan*/ * fbdefio; struct dlfb_data* par; } ;
struct dlfb_data {scalar_t__ fb_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  fb_mmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  dlfb_ops_mmap ; 
 int /*<<< orphan*/  fb_deferred_io_cleanup (struct fb_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlfb_ops_release(struct fb_info *info, int user)
{
	struct dlfb_data *dlfb = info->par;

	dlfb->fb_count--;

	if ((dlfb->fb_count == 0) && (info->fbdefio)) {
		fb_deferred_io_cleanup(info);
		kfree(info->fbdefio);
		info->fbdefio = NULL;
		info->fbops->fb_mmap = dlfb_ops_mmap;
	}

	dev_dbg(info->dev, "release, user=%d count=%d\n", user, dlfb->fb_count);

	return 0;
}