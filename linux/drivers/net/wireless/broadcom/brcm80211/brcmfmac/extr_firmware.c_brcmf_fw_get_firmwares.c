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
struct brcmf_fw_request {struct brcmf_fw_item* items; } ;
struct brcmf_fw_item {int /*<<< orphan*/  path; } ;
struct brcmf_fw {void (* done ) (struct device*,int,struct brcmf_fw_request*) ;struct device* dev; struct brcmf_fw_request* req; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_fw_request_done (int /*<<< orphan*/ *,struct brcmf_fw*) ; 
 int /*<<< orphan*/  brcmf_fw_request_is_valid (struct brcmf_fw_request*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct brcmf_fw* kzalloc (int,int /*<<< orphan*/ ) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,struct brcmf_fw*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,struct brcmf_fw*)) ; 

int brcmf_fw_get_firmwares(struct device *dev, struct brcmf_fw_request *req,
			   void (*fw_cb)(struct device *dev, int err,
					 struct brcmf_fw_request *req))
{
	struct brcmf_fw_item *first = &req->items[0];
	struct brcmf_fw *fwctx;
	int ret;

	brcmf_dbg(TRACE, "enter: dev=%s\n", dev_name(dev));
	if (!fw_cb)
		return -EINVAL;

	if (!brcmf_fw_request_is_valid(req))
		return -EINVAL;

	fwctx = kzalloc(sizeof(*fwctx), GFP_KERNEL);
	if (!fwctx)
		return -ENOMEM;

	fwctx->dev = dev;
	fwctx->req = req;
	fwctx->done = fw_cb;

	ret = request_firmware_nowait(THIS_MODULE, true, first->path,
				      fwctx->dev, GFP_KERNEL, fwctx,
				      brcmf_fw_request_done);
	if (ret < 0)
		brcmf_fw_request_done(NULL, fwctx);

	return 0;
}