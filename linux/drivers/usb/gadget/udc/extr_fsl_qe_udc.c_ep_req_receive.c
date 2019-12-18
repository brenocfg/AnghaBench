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
struct qe_req {int dummy; } ;
struct qe_ep {scalar_t__ state; scalar_t__ has_data; } ;

/* Variables and functions */
 scalar_t__ EP_STATE_NACK ; 
 int /*<<< orphan*/  ep_req_rx (struct qe_ep*,struct qe_req*) ; 
 int /*<<< orphan*/  qe_eprx_normal (struct qe_ep*) ; 

__attribute__((used)) static int ep_req_receive(struct qe_ep *ep, struct qe_req *req)
{
	if (ep->state == EP_STATE_NACK) {
		if (ep->has_data <= 0) {
			/* Enable rx and unmask rx interrupt */
			qe_eprx_normal(ep);
		} else {
			/* Copy the exist BD data */
			ep_req_rx(ep, req);
		}
	}

	return 0;
}