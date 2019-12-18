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
typedef  int u8 ;
struct mei_device {scalar_t__ dev_state; int /*<<< orphan*/  bus_rescan_work; } ;
struct hbm_props_response {int dummy; } ;
struct hbm_add_client_request {int /*<<< orphan*/  me_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ MEI_DEV_ENABLED ; 
 int MEI_HBMS_SUCCESS ; 
 int mei_hbm_add_cl_resp (struct mei_device*,int /*<<< orphan*/ ,int) ; 
 int mei_hbm_me_cl_add (struct mei_device*,struct hbm_props_response*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mei_hbm_fw_add_cl_req(struct mei_device *dev,
			      struct hbm_add_client_request *req)
{
	int ret;
	u8 status = MEI_HBMS_SUCCESS;

	BUILD_BUG_ON(sizeof(struct hbm_add_client_request) !=
			sizeof(struct hbm_props_response));

	ret = mei_hbm_me_cl_add(dev, (struct hbm_props_response *)req);
	if (ret)
		status = !MEI_HBMS_SUCCESS;

	if (dev->dev_state == MEI_DEV_ENABLED)
		schedule_work(&dev->bus_rescan_work);

	return mei_hbm_add_cl_resp(dev, req->me_addr, status);
}