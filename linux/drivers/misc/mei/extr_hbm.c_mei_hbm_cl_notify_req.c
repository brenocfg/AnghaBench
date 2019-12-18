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
typedef  int /*<<< orphan*/  u8 ;
struct mei_msg_hdr {int dummy; } ;
struct mei_device {int /*<<< orphan*/  dev; } ;
struct mei_cl {int dummy; } ;
struct hbm_notification_request {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEI_HBM_NOTIFY_REQ_CMD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mei_hbm_cl_hdr (struct mei_cl*,int /*<<< orphan*/ ,struct hbm_notification_request*,size_t const) ; 
 int /*<<< orphan*/  mei_hbm_hdr (struct mei_msg_hdr*,size_t const) ; 
 int mei_hbm_write_message (struct mei_device*,struct mei_msg_hdr*,struct hbm_notification_request*) ; 

int mei_hbm_cl_notify_req(struct mei_device *dev,
			  struct mei_cl *cl, u8 start)
{

	struct mei_msg_hdr mei_hdr;
	struct hbm_notification_request req;
	const size_t len = sizeof(struct hbm_notification_request);
	int ret;

	mei_hbm_hdr(&mei_hdr, len);
	mei_hbm_cl_hdr(cl, MEI_HBM_NOTIFY_REQ_CMD, &req, len);

	req.start = start;

	ret = mei_hbm_write_message(dev, &mei_hdr, &req);
	if (ret)
		dev_err(dev->dev, "notify request failed: ret = %d\n", ret);

	return ret;
}