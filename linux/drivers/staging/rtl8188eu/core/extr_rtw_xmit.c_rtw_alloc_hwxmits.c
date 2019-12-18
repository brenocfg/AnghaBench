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
struct xmit_priv {int /*<<< orphan*/  bk_pending; int /*<<< orphan*/  be_pending; int /*<<< orphan*/  vi_pending; int /*<<< orphan*/  vo_pending; struct hw_xmit* hwxmits; int /*<<< orphan*/  hwxmit_entry; } ;
struct hw_xmit {int /*<<< orphan*/ * sta_queue; } ;
struct adapter {struct xmit_priv xmitpriv; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HWXMIT_ENTRY ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 struct hw_xmit* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

s32 rtw_alloc_hwxmits(struct adapter *padapter)
{
	struct hw_xmit *hwxmits;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;

	pxmitpriv->hwxmit_entry = HWXMIT_ENTRY;

	pxmitpriv->hwxmits = kcalloc(pxmitpriv->hwxmit_entry,
				     sizeof(struct hw_xmit), GFP_KERNEL);
	if (!pxmitpriv->hwxmits)
		return _FAIL;

	hwxmits = pxmitpriv->hwxmits;

	hwxmits[0] .sta_queue = &pxmitpriv->vo_pending;
	hwxmits[1] .sta_queue = &pxmitpriv->vi_pending;
	hwxmits[2] .sta_queue = &pxmitpriv->be_pending;
	hwxmits[3] .sta_queue = &pxmitpriv->bk_pending;
	return _SUCCESS;
}