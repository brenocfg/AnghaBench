#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct capi_ctr {int dummy; } ;
struct TYPE_4__ {TYPE_2__* hyctrlinfo; } ;
typedef  TYPE_1__ hysdn_card ;
struct TYPE_5__ {struct capi_ctr capi_ctrl; } ;
typedef  TYPE_2__ hycapictrl_info ;

/* Variables and functions */
 int /*<<< orphan*/  hycapi_remove_ctr (struct capi_ctr*) ; 

int hycapi_capi_release(hysdn_card *card)
{
	hycapictrl_info *cinfo = card->hyctrlinfo;
	struct capi_ctr *ctrl;
#ifdef HYCAPI_PRINTFNAMES
	printk(KERN_NOTICE "hycapi_capi_release\n");
#endif
	if (cinfo) {
		ctrl = &cinfo->capi_ctrl;
		hycapi_remove_ctr(ctrl);
	}
	return 0;
}