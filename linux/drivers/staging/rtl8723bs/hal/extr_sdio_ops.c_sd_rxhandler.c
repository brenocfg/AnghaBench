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
struct __queue {int dummy; } ;
struct recv_priv {int /*<<< orphan*/  recv_tasklet; struct __queue recv_buf_pending_queue; } ;
struct recv_buf {int dummy; } ;
struct adapter {struct recv_priv recvpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_enqueue_recvbuf (struct recv_buf*,struct __queue*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sd_rxhandler(struct adapter *adapter, struct recv_buf *recvbuf)
{
	struct recv_priv *recv_priv;
	struct __queue *pending_queue;

	recv_priv = &adapter->recvpriv;
	pending_queue = &recv_priv->recv_buf_pending_queue;

	/* 3 1. enqueue recvbuf */
	rtw_enqueue_recvbuf(recvbuf, pending_queue);

	/* 3 2. schedule tasklet */
	tasklet_schedule(&recv_priv->recv_tasklet);
}