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
struct TYPE_4__ {TYPE_2__* hyctrlinfo; } ;
typedef  TYPE_1__ hysdn_card ;
struct TYPE_5__ {size_t out_idx; int /*<<< orphan*/  lock; int /*<<< orphan*/  capi_ctrl; int /*<<< orphan*/  sk_count; int /*<<< orphan*/ ** skbs; } ;
typedef  TYPE_2__ hycapictrl_info ;

/* Variables and functions */
 size_t HYSDN_MAX_CAPI_SKB ; 
 int /*<<< orphan*/  capi_ctr_resume_output (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void hycapi_tx_capiack(hysdn_card *card)
{
	hycapictrl_info *cinfo = card->hyctrlinfo;
#ifdef HYCAPI_PRINTFNAMES
	printk(KERN_NOTICE "hycapi_tx_capiack\n");
#endif
	if (!cinfo) {
		return;
	}
	spin_lock_irq(&cinfo->lock);
	kfree_skb(cinfo->skbs[cinfo->out_idx]);		/* free skb */
	cinfo->skbs[cinfo->out_idx++] = NULL;
	if (cinfo->out_idx >= HYSDN_MAX_CAPI_SKB)
		cinfo->out_idx = 0;	/* wrap around */

	if (cinfo->sk_count-- == HYSDN_MAX_CAPI_SKB)	/* dec usage count */
		capi_ctr_resume_output(&cinfo->capi_ctrl);
	spin_unlock_irq(&cinfo->lock);
}