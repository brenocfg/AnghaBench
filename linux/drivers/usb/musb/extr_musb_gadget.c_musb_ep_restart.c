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
struct musb_request {scalar_t__ tx; int /*<<< orphan*/  epnum; } ;
struct musb {int /*<<< orphan*/  mregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  musb_ep_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxstate (struct musb*,struct musb_request*) ; 
 int /*<<< orphan*/  trace_musb_req_start (struct musb_request*) ; 
 int /*<<< orphan*/  txstate (struct musb*,struct musb_request*) ; 

void musb_ep_restart(struct musb *musb, struct musb_request *req)
{
	trace_musb_req_start(req);
	musb_ep_select(musb->mregs, req->epnum);
	if (req->tx)
		txstate(musb, req);
	else
		rxstate(musb, req);
}