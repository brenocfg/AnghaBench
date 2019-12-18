#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct _adapter* adapter; } ;
struct TYPE_5__ {TYPE_1__ hdr; int /*<<< orphan*/  list; } ;
union recv_frame {TYPE_2__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  queue; } ;
struct recv_priv {int free_recvframe_cnt; int rx_pending_cnt; TYPE_3__ free_recv_queue; int /*<<< orphan*/ * precv_frame_buf; int /*<<< orphan*/ * pallocated_frame_buf; struct _adapter* adapter; TYPE_3__ recv_pending_queue; int /*<<< orphan*/  lock; } ;
struct _adapter {int dummy; } ;
typedef  int sint ;
typedef  int addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NR_RECVFRAME ; 
 int RXFRAME_ALIGN_SZ ; 
 int /*<<< orphan*/  _init_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  kmemleak_not_leak (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r8712_init_recv_priv (struct recv_priv*,struct _adapter*) ; 
 int /*<<< orphan*/  r8712_os_recv_resource_alloc (struct _adapter*,union recv_frame*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void _r8712_init_recv_priv(struct recv_priv *precvpriv,
			   struct _adapter *padapter)
{
	sint i;
	union recv_frame *precvframe;

	memset((unsigned char *)precvpriv, 0, sizeof(struct  recv_priv));
	spin_lock_init(&precvpriv->lock);
	_init_queue(&precvpriv->free_recv_queue);
	_init_queue(&precvpriv->recv_pending_queue);
	precvpriv->adapter = padapter;
	precvpriv->free_recvframe_cnt = NR_RECVFRAME;
	precvpriv->pallocated_frame_buf = kzalloc(NR_RECVFRAME *
				sizeof(union recv_frame) + RXFRAME_ALIGN_SZ,
				GFP_ATOMIC);
	if (precvpriv->pallocated_frame_buf == NULL)
		return;
	kmemleak_not_leak(precvpriv->pallocated_frame_buf);
	precvpriv->precv_frame_buf = precvpriv->pallocated_frame_buf +
				    RXFRAME_ALIGN_SZ -
				    ((addr_t)(precvpriv->pallocated_frame_buf) &
				    (RXFRAME_ALIGN_SZ - 1));
	precvframe = (union recv_frame *)precvpriv->precv_frame_buf;
	for (i = 0; i < NR_RECVFRAME; i++) {
		INIT_LIST_HEAD(&(precvframe->u.list));
		list_add_tail(&(precvframe->u.list),
				 &(precvpriv->free_recv_queue.queue));
		r8712_os_recv_resource_alloc(padapter, precvframe);
		precvframe->u.hdr.adapter = padapter;
		precvframe++;
	}
	precvpriv->rx_pending_cnt = 1;
	r8712_init_recv_priv(precvpriv, padapter);
}