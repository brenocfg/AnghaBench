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
struct TYPE_4__ {scalar_t__ len; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pseudo_palette; TYPE_2__ cmap; } ;
struct vivid_dev {int /*<<< orphan*/ * video_vbase; TYPE_1__ fb_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_dealloc_cmap (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void vivid_fb_release_buffers(struct vivid_dev *dev)
{
	if (dev->video_vbase == NULL)
		return;

	/* Release cmap */
	if (dev->fb_info.cmap.len)
		fb_dealloc_cmap(&dev->fb_info.cmap);

	/* Release pseudo palette */
	kfree(dev->fb_info.pseudo_palette);
	kfree(dev->video_vbase);
}