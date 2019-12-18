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
struct TYPE_3__ {struct osd_info* pseudo_palette; TYPE_2__ cmap; } ;
struct osd_info {int /*<<< orphan*/  wc_cookie; TYPE_1__ ivtvfb_info; } ;
struct ivtv {struct osd_info* osd_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct osd_info*) ; 

__attribute__((used)) static void ivtvfb_release_buffers (struct ivtv *itv)
{
	struct osd_info *oi = itv->osd_info;

	/* Release cmap */
	if (oi->ivtvfb_info.cmap.len)
		fb_dealloc_cmap(&oi->ivtvfb_info.cmap);

	/* Release pseudo palette */
	kfree(oi->ivtvfb_info.pseudo_palette);
	arch_phys_wc_del(oi->wc_cookie);
	kfree(oi);
	itv->osd_info = NULL;
}