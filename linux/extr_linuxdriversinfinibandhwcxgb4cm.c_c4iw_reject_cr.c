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
typedef  int /*<<< orphan*/  u8 ;
struct iw_cm_id {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/  history; } ;
struct c4iw_ep {TYPE_1__ com; int /*<<< orphan*/  hwtid; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MPA_REQ_RCVD ; 
 int /*<<< orphan*/  ULP_REJECT ; 
 int /*<<< orphan*/  c4iw_ep_disconnect (struct c4iw_ep*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c4iw_put_ep (TYPE_1__*) ; 
 scalar_t__ mpa_rev ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct c4iw_ep*,int /*<<< orphan*/ ) ; 
 int send_mpa_reject (struct c4iw_ep*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_ep_timer (struct c4iw_ep*) ; 
 struct c4iw_ep* to_ep (struct iw_cm_id*) ; 

int c4iw_reject_cr(struct iw_cm_id *cm_id, const void *pdata, u8 pdata_len)
{
	int abort;
	struct c4iw_ep *ep = to_ep(cm_id);

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);

	mutex_lock(&ep->com.mutex);
	if (ep->com.state != MPA_REQ_RCVD) {
		mutex_unlock(&ep->com.mutex);
		c4iw_put_ep(&ep->com);
		return -ECONNRESET;
	}
	set_bit(ULP_REJECT, &ep->com.history);
	if (mpa_rev == 0)
		abort = 1;
	else
		abort = send_mpa_reject(ep, pdata, pdata_len);
	mutex_unlock(&ep->com.mutex);

	stop_ep_timer(ep);
	c4iw_ep_disconnect(ep, abort != 0, GFP_KERNEL);
	c4iw_put_ep(&ep->com);
	return 0;
}