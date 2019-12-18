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
struct pkt_attrib {int /*<<< orphan*/  priority; int /*<<< orphan*/  ra; struct sta_info* psta; } ;
struct xmit_frame {int /*<<< orphan*/  list; struct pkt_attrib attrib; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;
struct tx_servq {int /*<<< orphan*/  qcnt; TYPE_1__ sta_pending; int /*<<< orphan*/  tx_pending; } ;
struct sta_priv {int dummy; } ;
struct sta_info {int dummy; } ;
struct mlme_priv {int dummy; } ;
struct _adapter {struct mlme_priv mlmepriv; struct sta_priv stapriv; } ;
struct __queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WIFI_MP_STATE ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bssid (struct mlme_priv*) ; 
 struct tx_servq* get_sta_pending (struct _adapter*,struct __queue**,struct sta_info*,int /*<<< orphan*/ ) ; 
 int is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct sta_info* r8712_get_bcmc_stainfo (struct _adapter*) ; 
 struct sta_info* r8712_get_stainfo (struct sta_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int r8712_xmit_classifier(struct _adapter *padapter,
			  struct xmit_frame *pxmitframe)
{
	unsigned long irqL0;
	struct  __queue *pstapending;
	struct sta_info	*psta;
	struct tx_servq	*ptxservq;
	struct pkt_attrib *pattrib = &pxmitframe->attrib;
	struct sta_priv *pstapriv = &padapter->stapriv;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	bool bmcst = is_multicast_ether_addr(pattrib->ra);

	if (pattrib->psta) {
		psta = pattrib->psta;
	} else {
		if (bmcst) {
			psta = r8712_get_bcmc_stainfo(padapter);
		} else {
			if (check_fwstate(pmlmepriv, WIFI_MP_STATE))
				psta = r8712_get_stainfo(pstapriv,
				       get_bssid(pmlmepriv));
			else
				psta = r8712_get_stainfo(pstapriv, pattrib->ra);
		}
	}
	if (psta == NULL)
		return -EINVAL;
	ptxservq = get_sta_pending(padapter, &pstapending,
		   psta, pattrib->priority);
	spin_lock_irqsave(&pstapending->lock, irqL0);
	if (list_empty(&ptxservq->tx_pending))
		list_add_tail(&ptxservq->tx_pending, &pstapending->queue);
	list_add_tail(&pxmitframe->list, &ptxservq->sta_pending.queue);
	ptxservq->qcnt++;
	spin_unlock_irqrestore(&pstapending->lock, irqL0);
	return 0;
}