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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  users; struct ll_header* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_errors; } ;
struct netiucv_priv {TYPE_2__ stats; } ;
struct ll_header {scalar_t__ next; } ;
struct iucv_message {int tag; scalar_t__ class; } ;
struct TYPE_3__ {scalar_t__ txlen; scalar_t__ tx_pending; scalar_t__ tx_max_pending; int /*<<< orphan*/  doios_single; int /*<<< orphan*/  send_stamp; } ;
struct iucv_connection {scalar_t__ collect_len; scalar_t__ max_buffsize; int /*<<< orphan*/  commit_queue; int /*<<< orphan*/  netdev; TYPE_1__ prof; int /*<<< orphan*/  fsm; int /*<<< orphan*/  path; int /*<<< orphan*/  collect_lock; int /*<<< orphan*/  collect_queue; } ;

/* Variables and functions */
 scalar_t__ CONN_STATE_IDLE ; 
 scalar_t__ CONN_STATE_TX ; 
 int EBUSY ; 
 int ENOMEM ; 
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 int /*<<< orphan*/  IUCV_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  IUCV_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,int) ; 
 scalar_t__ NETIUCV_HDRLEN ; 
 struct sk_buff* alloc_skb (scalar_t__,int) ; 
 int /*<<< orphan*/  data ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ fsm_getstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsm_newstate (int /*<<< orphan*/ ,scalar_t__) ; 
 int iucv_message_send (int /*<<< orphan*/ ,struct iucv_message*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ll_header*,scalar_t__) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ll_header*,scalar_t__) ; 
 struct netiucv_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,struct ll_header*,scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_tail_pointer (struct sk_buff*) ; 
 int skb_tailroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int netiucv_transmit_skb(struct iucv_connection *conn,
				struct sk_buff *skb)
{
	struct iucv_message msg;
	unsigned long saveflags;
	struct ll_header header;
	int rc;

	if (fsm_getstate(conn->fsm) != CONN_STATE_IDLE) {
		int l = skb->len + NETIUCV_HDRLEN;

		spin_lock_irqsave(&conn->collect_lock, saveflags);
		if (conn->collect_len + l >
		    (conn->max_buffsize - NETIUCV_HDRLEN)) {
			rc = -EBUSY;
			IUCV_DBF_TEXT(data, 2,
				      "EBUSY from netiucv_transmit_skb\n");
		} else {
			refcount_inc(&skb->users);
			skb_queue_tail(&conn->collect_queue, skb);
			conn->collect_len += l;
			rc = 0;
		}
		spin_unlock_irqrestore(&conn->collect_lock, saveflags);
	} else {
		struct sk_buff *nskb = skb;
		/**
		 * Copy the skb to a new allocated skb in lowmem only if the
		 * data is located above 2G in memory or tailroom is < 2.
		 */
		unsigned long hi = ((unsigned long)(skb_tail_pointer(skb) +
				    NETIUCV_HDRLEN)) >> 31;
		int copied = 0;
		if (hi || (skb_tailroom(skb) < 2)) {
			nskb = alloc_skb(skb->len + NETIUCV_HDRLEN +
					 NETIUCV_HDRLEN, GFP_ATOMIC | GFP_DMA);
			if (!nskb) {
				IUCV_DBF_TEXT(data, 2, "alloc_skb failed\n");
				rc = -ENOMEM;
				return rc;
			} else {
				skb_reserve(nskb, NETIUCV_HDRLEN);
				skb_put_data(nskb, skb->data, skb->len);
			}
			copied = 1;
		}
		/**
		 * skb now is below 2G and has enough room. Add headers.
		 */
		header.next = nskb->len + NETIUCV_HDRLEN;
		memcpy(skb_push(nskb, NETIUCV_HDRLEN), &header, NETIUCV_HDRLEN);
		header.next = 0;
		skb_put_data(nskb, &header, NETIUCV_HDRLEN);

		fsm_newstate(conn->fsm, CONN_STATE_TX);
		conn->prof.send_stamp = jiffies;

		msg.tag = 1;
		msg.class = 0;
		rc = iucv_message_send(conn->path, &msg, 0, 0,
				       nskb->data, nskb->len);
		conn->prof.doios_single++;
		conn->prof.txlen += skb->len;
		conn->prof.tx_pending++;
		if (conn->prof.tx_pending > conn->prof.tx_max_pending)
			conn->prof.tx_max_pending = conn->prof.tx_pending;
		if (rc) {
			struct netiucv_priv *privptr;
			fsm_newstate(conn->fsm, CONN_STATE_IDLE);
			conn->prof.tx_pending--;
			privptr = netdev_priv(conn->netdev);
			if (privptr)
				privptr->stats.tx_errors++;
			if (copied)
				dev_kfree_skb(nskb);
			else {
				/**
				 * Remove our headers. They get added
				 * again on retransmit.
				 */
				skb_pull(skb, NETIUCV_HDRLEN);
				skb_trim(skb, skb->len - NETIUCV_HDRLEN);
			}
			IUCV_DBF_TEXT_(data, 2, "rc %d from iucv_send\n", rc);
		} else {
			if (copied)
				dev_kfree_skb(skb);
			refcount_inc(&nskb->users);
			skb_queue_tail(&conn->commit_queue, nskb);
		}
	}

	return rc;
}