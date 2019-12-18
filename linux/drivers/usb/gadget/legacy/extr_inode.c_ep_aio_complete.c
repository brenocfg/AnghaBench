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
struct usb_request {scalar_t__ actual; scalar_t__ status; struct kiocb_priv* buf; struct kiocb* context; } ;
struct usb_ep {int /*<<< orphan*/  name; } ;
struct kiocb_priv {scalar_t__ actual; int /*<<< orphan*/  work; struct kiocb_priv* buf; struct kiocb_priv* to_free; struct ep_data* epdata; int /*<<< orphan*/ * req; } ;
struct kiocb {int /*<<< orphan*/  (* ki_complete ) (struct kiocb*,scalar_t__,scalar_t__) ;struct kiocb_priv* private; } ;
struct ep_data {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (TYPE_1__*,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep_user_copy_worker ; 
 int /*<<< orphan*/  kfree (struct kiocb_priv*) ; 
 int /*<<< orphan*/  put_ep (struct ep_data*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct kiocb*,scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_ep_free_request (struct usb_ep*,struct usb_request*) ; 

__attribute__((used)) static void ep_aio_complete(struct usb_ep *ep, struct usb_request *req)
{
	struct kiocb		*iocb = req->context;
	struct kiocb_priv	*priv = iocb->private;
	struct ep_data		*epdata = priv->epdata;

	/* lock against disconnect (and ideally, cancel) */
	spin_lock(&epdata->dev->lock);
	priv->req = NULL;
	priv->epdata = NULL;

	/* if this was a write or a read returning no data then we
	 * don't need to copy anything to userspace, so we can
	 * complete the aio request immediately.
	 */
	if (priv->to_free == NULL || unlikely(req->actual == 0)) {
		kfree(req->buf);
		kfree(priv->to_free);
		kfree(priv);
		iocb->private = NULL;
		/* aio_complete() reports bytes-transferred _and_ faults */

		iocb->ki_complete(iocb, req->actual ? req->actual : req->status,
				req->status);
	} else {
		/* ep_copy_to_user() won't report both; we hide some faults */
		if (unlikely(0 != req->status))
			DBG(epdata->dev, "%s fault %d len %d\n",
				ep->name, req->status, req->actual);

		priv->buf = req->buf;
		priv->actual = req->actual;
		INIT_WORK(&priv->work, ep_user_copy_worker);
		schedule_work(&priv->work);
	}

	usb_ep_free_request(ep, req);
	spin_unlock(&epdata->dev->lock);
	put_ep(epdata);
}