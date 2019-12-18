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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  status; int /*<<< orphan*/  list; } ;
struct cdns3_request {int flags; int /*<<< orphan*/  list; TYPE_2__ request; } ;
struct cdns3_endpoint {int flags; int num; int dir; int /*<<< orphan*/  wa2_descmiss_req_list; int /*<<< orphan*/  pending_req_list; } ;
struct cdns3_device {TYPE_1__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  ep_sts_en; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EP_QUIRK_EXTRA_BUF_DET ; 
 int EP_QUIRK_EXTRA_BUF_EN ; 
 int /*<<< orphan*/  EP_STS_EN_DESCMISEN ; 
 int REQUEST_INTERNAL ; 
 int /*<<< orphan*/  cdns3_gadget_giveback (struct cdns3_endpoint*,struct cdns3_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns3_select_ep (struct cdns3_device*,int) ; 
 int /*<<< orphan*/  cdns3_wa2_descmiss_copy_data (struct cdns3_endpoint*,TYPE_2__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_cdns3_wa2 (struct cdns3_endpoint*,char*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int cdns3_wa2_gadget_ep_queue(struct cdns3_device *priv_dev,
			      struct cdns3_endpoint *priv_ep,
			      struct cdns3_request *priv_req)
{
	int deferred = 0;

	/*
	 * If transfer was queued before DESCMISS appear than we
	 * can disable handling of DESCMISS interrupt. Driver assumes that it
	 * can disable special treatment for this endpoint.
	 */
	if (priv_ep->flags & EP_QUIRK_EXTRA_BUF_DET) {
		u32 reg;

		cdns3_select_ep(priv_dev, priv_ep->num | priv_ep->dir);
		priv_ep->flags &= ~EP_QUIRK_EXTRA_BUF_DET;
		reg = readl(&priv_dev->regs->ep_sts_en);
		reg &= ~EP_STS_EN_DESCMISEN;
		trace_cdns3_wa2(priv_ep, "workaround disabled\n");
		writel(reg, &priv_dev->regs->ep_sts_en);
	}

	if (priv_ep->flags & EP_QUIRK_EXTRA_BUF_EN) {
		u8 pending_empty = list_empty(&priv_ep->pending_req_list);
		u8 descmiss_empty = list_empty(&priv_ep->wa2_descmiss_req_list);

		/*
		 *  DESCMISS transfer has been finished, so data will be
		 *  directly copied from internal allocated usb_request
		 *  objects.
		 */
		if (pending_empty && !descmiss_empty &&
		    !(priv_req->flags & REQUEST_INTERNAL)) {
			cdns3_wa2_descmiss_copy_data(priv_ep,
						     &priv_req->request);

			trace_cdns3_wa2(priv_ep, "get internal stored data");

			list_add_tail(&priv_req->request.list,
				      &priv_ep->pending_req_list);
			cdns3_gadget_giveback(priv_ep, priv_req,
					      priv_req->request.status);

			/*
			 * Intentionally driver returns positive value as
			 * correct value. It informs that transfer has
			 * been finished.
			 */
			return EINPROGRESS;
		}

		/*
		 * Driver will wait for completion DESCMISS transfer,
		 * before starts new, not DESCMISS transfer.
		 */
		if (!pending_empty && !descmiss_empty) {
			trace_cdns3_wa2(priv_ep, "wait for pending transfer\n");
			deferred = 1;
		}

		if (priv_req->flags & REQUEST_INTERNAL)
			list_add_tail(&priv_req->list,
				      &priv_ep->wa2_descmiss_req_list);
	}

	return deferred;
}