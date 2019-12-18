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
struct mei_msg_hdr {int dummy; } ;
struct mei_device {int /*<<< orphan*/  init_clients_timer; int /*<<< orphan*/  hbm_state; int /*<<< orphan*/  dev; scalar_t__ hbm_f_ie_supported; scalar_t__ hbm_f_dc_supported; } ;
struct hbm_host_enum_request {int /*<<< orphan*/  flags; int /*<<< orphan*/  hbm_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_ENUM_REQ_CMD ; 
 int /*<<< orphan*/  MEI_CLIENTS_INIT_TIMEOUT ; 
 int /*<<< orphan*/  MEI_HBM_ENUM_CLIENTS ; 
 int /*<<< orphan*/  MEI_HBM_ENUM_F_ALLOW_ADD ; 
 int /*<<< orphan*/  MEI_HBM_ENUM_F_IMMEDIATE_ENUM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mei_hbm_hdr (struct mei_msg_hdr*,size_t const) ; 
 int mei_hbm_write_message (struct mei_device*,struct mei_msg_hdr*,struct hbm_host_enum_request*) ; 
 int /*<<< orphan*/  mei_schedule_stall_timer (struct mei_device*) ; 
 int /*<<< orphan*/  memset (struct hbm_host_enum_request*,int /*<<< orphan*/ ,size_t const) ; 

__attribute__((used)) static int mei_hbm_enum_clients_req(struct mei_device *dev)
{
	struct mei_msg_hdr mei_hdr;
	struct hbm_host_enum_request enum_req;
	const size_t len = sizeof(struct hbm_host_enum_request);
	int ret;

	/* enumerate clients */
	mei_hbm_hdr(&mei_hdr, len);

	memset(&enum_req, 0, len);
	enum_req.hbm_cmd = HOST_ENUM_REQ_CMD;
	enum_req.flags |= dev->hbm_f_dc_supported ?
			  MEI_HBM_ENUM_F_ALLOW_ADD : 0;
	enum_req.flags |= dev->hbm_f_ie_supported ?
			  MEI_HBM_ENUM_F_IMMEDIATE_ENUM : 0;

	ret = mei_hbm_write_message(dev, &mei_hdr, &enum_req);
	if (ret) {
		dev_err(dev->dev, "enumeration request write failed: ret = %d.\n",
			ret);
		return ret;
	}
	dev->hbm_state = MEI_HBM_ENUM_CLIENTS;
	dev->init_clients_timer = MEI_CLIENTS_INIT_TIMEOUT;
	mei_schedule_stall_timer(dev);
	return 0;
}