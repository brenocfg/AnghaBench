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
struct xmit_priv {int /*<<< orphan*/  tx_drop; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_pkts; } ;
struct TYPE_4__ {scalar_t__ last_txcmdsz; } ;
struct xmit_frame {TYPE_2__ attrib; int /*<<< orphan*/ * pkt; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* LedControlHandler ) (struct _adapter*,int /*<<< orphan*/ ) ;} ;
struct _adapter {TYPE_1__ ledpriv; struct xmit_priv xmitpriv; } ;
typedef  int /*<<< orphan*/  _pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LED_CTL_TX ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 struct _adapter* netdev_priv (struct net_device*) ; 
 struct xmit_frame* r8712_alloc_xmitframe (struct xmit_priv*) ; 
 int /*<<< orphan*/  r8712_free_xmitframe (struct xmit_priv*,struct xmit_frame*) ; 
 int /*<<< orphan*/  r8712_if_up (struct _adapter*) ; 
 scalar_t__ r8712_pre_xmit (struct _adapter*,struct xmit_frame*) ; 
 scalar_t__ r8712_update_attrib (struct _adapter*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct _adapter*,int /*<<< orphan*/ ) ; 

int r8712_xmit_entry(_pkt *pkt, struct  net_device *netdev)
{
	struct xmit_frame *xmitframe = NULL;
	struct _adapter *adapter = netdev_priv(netdev);
	struct xmit_priv *xmitpriv = &(adapter->xmitpriv);

	if (!r8712_if_up(adapter))
		goto _xmit_entry_drop;

	xmitframe = r8712_alloc_xmitframe(xmitpriv);
	if (!xmitframe)
		goto _xmit_entry_drop;

	if (r8712_update_attrib(adapter, pkt, &xmitframe->attrib))
		goto _xmit_entry_drop;

	adapter->ledpriv.LedControlHandler(adapter, LED_CTL_TX);
	xmitframe->pkt = pkt;
	if (r8712_pre_xmit(adapter, xmitframe)) {
		/*dump xmitframe directly or drop xframe*/
		dev_kfree_skb_any(pkt);
		xmitframe->pkt = NULL;
	}
	xmitpriv->tx_pkts++;
	xmitpriv->tx_bytes += xmitframe->attrib.last_txcmdsz;
	return 0;
_xmit_entry_drop:
	if (xmitframe)
		r8712_free_xmitframe(xmitpriv, xmitframe);
	xmitpriv->tx_drop++;
	dev_kfree_skb_any(pkt);
	return 0;
}