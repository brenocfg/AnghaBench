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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/  data; scalar_t__ (* notify_link_chg ) (struct cgx_link_event*,int /*<<< orphan*/ ) ;} ;
struct cgx_link_user_info {int /*<<< orphan*/  speed; scalar_t__ link_up; } ;
struct lmac {int /*<<< orphan*/  event_cb_lock; TYPE_2__ event_cb; int /*<<< orphan*/  lmac_id; struct cgx_link_user_info link_info; struct cgx* cgx; } ;
struct device {int dummy; } ;
struct cgx_link_event {struct cgx_link_user_info link_uinfo; int /*<<< orphan*/  lmac_id; int /*<<< orphan*/  cgx_id; } ;
struct cgx {int /*<<< orphan*/  cgx_id; TYPE_1__* pdev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int CGX_ERR_NONE ; 
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESP_LINKSTAT_ERRTYPE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_status_user_format (int /*<<< orphan*/ ,struct cgx_link_user_info*,struct cgx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct cgx_link_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cgx_link_change_handler(u64 lstat,
					   struct lmac *lmac)
{
	struct cgx_link_user_info *linfo;
	struct cgx *cgx = lmac->cgx;
	struct cgx_link_event event;
	struct device *dev;
	int err_type;

	dev = &cgx->pdev->dev;

	link_status_user_format(lstat, &event.link_uinfo, cgx, lmac->lmac_id);
	err_type = FIELD_GET(RESP_LINKSTAT_ERRTYPE, lstat);

	event.cgx_id = cgx->cgx_id;
	event.lmac_id = lmac->lmac_id;

	/* update the local copy of link status */
	lmac->link_info = event.link_uinfo;
	linfo = &lmac->link_info;

	/* Ensure callback doesn't get unregistered until we finish it */
	spin_lock(&lmac->event_cb_lock);

	if (!lmac->event_cb.notify_link_chg) {
		dev_dbg(dev, "cgx port %d:%d Link change handler null",
			cgx->cgx_id, lmac->lmac_id);
		if (err_type != CGX_ERR_NONE) {
			dev_err(dev, "cgx port %d:%d Link error %d\n",
				cgx->cgx_id, lmac->lmac_id, err_type);
		}
		dev_info(dev, "cgx port %d:%d Link is %s %d Mbps\n",
			 cgx->cgx_id, lmac->lmac_id,
			 linfo->link_up ? "UP" : "DOWN", linfo->speed);
		goto err;
	}

	if (lmac->event_cb.notify_link_chg(&event, lmac->event_cb.data))
		dev_err(dev, "event notification failure\n");
err:
	spin_unlock(&lmac->event_cb_lock);
}