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
struct TYPE_4__ {unsigned int length; unsigned int actual; unsigned int buf; scalar_t__ zero; } ;
struct usba_request {int last_transaction; TYPE_2__ req; } ;
struct TYPE_3__ {unsigned int maxpacket; int /*<<< orphan*/  name; } ;
struct usba_ep {int /*<<< orphan*/  fifo; TYPE_1__ ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct usba_request*,unsigned int,char*) ; 
 int /*<<< orphan*/  DBG_QUEUE ; 
 int /*<<< orphan*/  SET_STA ; 
 int /*<<< orphan*/  USBA_TX_PK_RDY ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  usba_ep_writel (struct usba_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void next_fifo_transaction(struct usba_ep *ep, struct usba_request *req)
{
	unsigned int transaction_len;

	transaction_len = req->req.length - req->req.actual;
	req->last_transaction = 1;
	if (transaction_len > ep->ep.maxpacket) {
		transaction_len = ep->ep.maxpacket;
		req->last_transaction = 0;
	} else if (transaction_len == ep->ep.maxpacket && req->req.zero)
		req->last_transaction = 0;

	DBG(DBG_QUEUE, "%s: submit_transaction, req %p (length %d)%s\n",
		ep->ep.name, req, transaction_len,
		req->last_transaction ? ", done" : "");

	memcpy_toio(ep->fifo, req->req.buf + req->req.actual, transaction_len);
	usba_ep_writel(ep, SET_STA, USBA_TX_PK_RDY);
	req->req.actual += transaction_len;
}