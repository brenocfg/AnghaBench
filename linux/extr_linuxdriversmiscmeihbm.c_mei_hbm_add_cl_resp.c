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
typedef  void* u8 ;
struct mei_msg_hdr {int dummy; } ;
struct mei_device {int /*<<< orphan*/  dev; } ;
struct hbm_add_client_response {void* status; void* me_addr; int /*<<< orphan*/  hbm_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEI_HBM_ADD_CLIENT_RES_CMD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mei_hbm_hdr (struct mei_msg_hdr*,size_t const) ; 
 int mei_hbm_write_message (struct mei_device*,struct mei_msg_hdr*,struct hbm_add_client_response*) ; 
 int /*<<< orphan*/  memset (struct hbm_add_client_response*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mei_hbm_add_cl_resp(struct mei_device *dev, u8 addr, u8 status)
{
	struct mei_msg_hdr mei_hdr;
	struct hbm_add_client_response resp;
	const size_t len = sizeof(struct hbm_add_client_response);
	int ret;

	dev_dbg(dev->dev, "adding client response\n");

	mei_hbm_hdr(&mei_hdr, len);

	memset(&resp, 0, sizeof(struct hbm_add_client_response));
	resp.hbm_cmd = MEI_HBM_ADD_CLIENT_RES_CMD;
	resp.me_addr = addr;
	resp.status  = status;

	ret = mei_hbm_write_message(dev, &mei_hdr, &resp);
	if (ret)
		dev_err(dev->dev, "add client response write failed: ret = %d\n",
			ret);
	return ret;
}