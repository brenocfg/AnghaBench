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
struct TYPE_2__ {scalar_t__ head; } ;
struct xmit_priv {int hwxmit_entry; int /*<<< orphan*/  bk_pending; TYPE_1__ bk_txqueue; int /*<<< orphan*/  be_pending; TYPE_1__ be_txqueue; int /*<<< orphan*/  vi_pending; TYPE_1__ vi_txqueue; int /*<<< orphan*/  vo_pending; TYPE_1__ vo_txqueue; int /*<<< orphan*/  bm_pending; TYPE_1__ bmc_txqueue; struct hw_xmit* hwxmits; } ;
struct hw_xmit {int /*<<< orphan*/ * sta_queue; TYPE_1__* phwtxqueue; } ;
struct _adapter {struct xmit_priv xmitpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HWXMIT_ENTRY ; 
 struct hw_xmit* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alloc_hwxmits(struct _adapter *padapter)
{
	struct hw_xmit *hwxmits;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;

	pxmitpriv->hwxmit_entry = HWXMIT_ENTRY;
	pxmitpriv->hwxmits = kmalloc_array(pxmitpriv->hwxmit_entry,
				sizeof(struct hw_xmit), GFP_ATOMIC);
	if (!pxmitpriv->hwxmits)
		return;
	hwxmits = pxmitpriv->hwxmits;
	if (pxmitpriv->hwxmit_entry == 5) {
		pxmitpriv->bmc_txqueue.head = 0;
		hwxmits[0] .phwtxqueue = &pxmitpriv->bmc_txqueue;
		hwxmits[0] .sta_queue = &pxmitpriv->bm_pending;
		pxmitpriv->vo_txqueue.head = 0;
		hwxmits[1] .phwtxqueue = &pxmitpriv->vo_txqueue;
		hwxmits[1] .sta_queue = &pxmitpriv->vo_pending;
		pxmitpriv->vi_txqueue.head = 0;
		hwxmits[2] .phwtxqueue = &pxmitpriv->vi_txqueue;
		hwxmits[2] .sta_queue = &pxmitpriv->vi_pending;
		pxmitpriv->bk_txqueue.head = 0;
		hwxmits[3] .phwtxqueue = &pxmitpriv->bk_txqueue;
		hwxmits[3] .sta_queue = &pxmitpriv->bk_pending;
		pxmitpriv->be_txqueue.head = 0;
		hwxmits[4] .phwtxqueue = &pxmitpriv->be_txqueue;
		hwxmits[4] .sta_queue = &pxmitpriv->be_pending;
	} else if (pxmitpriv->hwxmit_entry == 4) {
		pxmitpriv->vo_txqueue.head = 0;
		hwxmits[0] .phwtxqueue = &pxmitpriv->vo_txqueue;
		hwxmits[0] .sta_queue = &pxmitpriv->vo_pending;
		pxmitpriv->vi_txqueue.head = 0;
		hwxmits[1] .phwtxqueue = &pxmitpriv->vi_txqueue;
		hwxmits[1] .sta_queue = &pxmitpriv->vi_pending;
		pxmitpriv->be_txqueue.head = 0;
		hwxmits[2] .phwtxqueue = &pxmitpriv->be_txqueue;
		hwxmits[2] .sta_queue = &pxmitpriv->be_pending;
		pxmitpriv->bk_txqueue.head = 0;
		hwxmits[3] .phwtxqueue = &pxmitpriv->bk_txqueue;
		hwxmits[3] .sta_queue = &pxmitpriv->bk_pending;
	}
}