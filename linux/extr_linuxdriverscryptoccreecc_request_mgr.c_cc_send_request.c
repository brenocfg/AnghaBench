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
struct device {int dummy; } ;
struct crypto_async_request {int flags; } ;
struct cc_req_mgr_handle {int /*<<< orphan*/  hw_lock; } ;
struct cc_hw_desc {int /*<<< orphan*/  ivgen_dma_addr_len; } ;
struct cc_drvdata {struct cc_req_mgr_handle* request_mgr_handle; } ;
struct cc_crypto_req {int /*<<< orphan*/  ivgen_dma_addr_len; } ;
struct cc_bl_item {unsigned int len; int notif; int /*<<< orphan*/  desc; int /*<<< orphan*/  creq; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 unsigned int CC_IVPOOL_SEQ_LEN ; 
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int EBUSY ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int cc_do_send_request (struct cc_drvdata*,struct cc_hw_desc*,struct cc_hw_desc*,unsigned int,int,int) ; 
 int /*<<< orphan*/  cc_enqueue_backlog (struct cc_drvdata*,struct cc_bl_item*) ; 
 int /*<<< orphan*/  cc_gfp_flags (struct crypto_async_request*) ; 
 int cc_pm_get (struct device*) ; 
 int /*<<< orphan*/  cc_pm_put_suspend (struct device*) ; 
 int cc_queues_status (struct cc_drvdata*,struct cc_req_mgr_handle*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 
 struct cc_bl_item* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct cc_hw_desc*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int cc_send_request(struct cc_drvdata *drvdata, struct cc_crypto_req *cc_req,
		    struct cc_hw_desc *desc, unsigned int len,
		    struct crypto_async_request *req)
{
	int rc;
	struct cc_req_mgr_handle *mgr = drvdata->request_mgr_handle;
	bool ivgen = !!cc_req->ivgen_dma_addr_len;
	unsigned int total_len = len + (ivgen ? CC_IVPOOL_SEQ_LEN : 0);
	struct device *dev = drvdata_to_dev(drvdata);
	bool backlog_ok = req->flags & CRYPTO_TFM_REQ_MAY_BACKLOG;
	gfp_t flags = cc_gfp_flags(req);
	struct cc_bl_item *bli;

	rc = cc_pm_get(dev);
	if (rc) {
		dev_err(dev, "ssi_power_mgr_runtime_get returned %x\n", rc);
		return rc;
	}

	spin_lock_bh(&mgr->hw_lock);
	rc = cc_queues_status(drvdata, mgr, total_len);

#ifdef CC_DEBUG_FORCE_BACKLOG
	if (backlog_ok)
		rc = -ENOSPC;
#endif /* CC_DEBUG_FORCE_BACKLOG */

	if (rc == -ENOSPC && backlog_ok) {
		spin_unlock_bh(&mgr->hw_lock);

		bli = kmalloc(sizeof(*bli), flags);
		if (!bli) {
			cc_pm_put_suspend(dev);
			return -ENOMEM;
		}

		memcpy(&bli->creq, cc_req, sizeof(*cc_req));
		memcpy(&bli->desc, desc, len * sizeof(*desc));
		bli->len = len;
		bli->notif = false;
		cc_enqueue_backlog(drvdata, bli);
		return -EBUSY;
	}

	if (!rc)
		rc = cc_do_send_request(drvdata, cc_req, desc, len, false,
					ivgen);

	spin_unlock_bh(&mgr->hw_lock);
	return rc;
}