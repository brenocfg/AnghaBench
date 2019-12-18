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
struct ishtp_msg_hdr {int dummy; } ;
struct ishtp_device {int /*<<< orphan*/  hbm_state; int /*<<< orphan*/  devc; int /*<<< orphan*/  dev_state; } ;
struct hbm_host_enum_request {int /*<<< orphan*/  hbm_cmd; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  enum_req ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_ENUM_REQ_CMD ; 
 int /*<<< orphan*/  ISHTP_DEV_RESETTING ; 
 int /*<<< orphan*/  ISHTP_HBM_ENUM_CLIENTS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ish_hw_reset (struct ishtp_device*) ; 
 int /*<<< orphan*/  ishtp_hbm_hdr (struct ishtp_msg_hdr*,int) ; 
 scalar_t__ ishtp_write_message (struct ishtp_device*,struct ishtp_msg_hdr*,struct hbm_host_enum_request*) ; 

void ishtp_hbm_enum_clients_req(struct ishtp_device *dev)
{
	struct ishtp_msg_hdr hdr;
	struct hbm_host_enum_request enum_req = { 0 };

	/* enumerate clients */
	ishtp_hbm_hdr(&hdr, sizeof(enum_req));
	enum_req.hbm_cmd = HOST_ENUM_REQ_CMD;

	if (ishtp_write_message(dev, &hdr, &enum_req)) {
		dev->dev_state = ISHTP_DEV_RESETTING;
		dev_err(dev->devc, "enumeration request send failed\n");
		ish_hw_reset(dev);
	}
	dev->hbm_state = ISHTP_HBM_ENUM_CLIENTS;
}