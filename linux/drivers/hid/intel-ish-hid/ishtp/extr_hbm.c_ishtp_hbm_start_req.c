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
struct ishtp_msg_hdr {int dummy; } ;
struct ishtp_device {int /*<<< orphan*/  hbm_state; int /*<<< orphan*/  dev_state; int /*<<< orphan*/  devc; } ;
struct TYPE_2__ {int /*<<< orphan*/  minor_version; int /*<<< orphan*/  major_version; } ;
struct hbm_host_version_request {TYPE_1__ host_version; int /*<<< orphan*/  hbm_cmd; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  start_req ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HBM_MAJOR_VERSION ; 
 int /*<<< orphan*/  HBM_MINOR_VERSION ; 
 int /*<<< orphan*/  HOST_START_REQ_CMD ; 
 int /*<<< orphan*/  ISHTP_DEV_RESETTING ; 
 int /*<<< orphan*/  ISHTP_HBM_IDLE ; 
 int /*<<< orphan*/  ISHTP_HBM_START ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ish_hw_reset (struct ishtp_device*) ; 
 int /*<<< orphan*/  ishtp_hbm_hdr (struct ishtp_msg_hdr*,int) ; 
 scalar_t__ ishtp_write_message (struct ishtp_device*,struct ishtp_msg_hdr*,struct hbm_host_version_request*) ; 

int ishtp_hbm_start_req(struct ishtp_device *dev)
{
	struct ishtp_msg_hdr hdr;
	struct hbm_host_version_request start_req = { 0 };

	ishtp_hbm_hdr(&hdr, sizeof(start_req));

	/* host start message */
	start_req.hbm_cmd = HOST_START_REQ_CMD;
	start_req.host_version.major_version = HBM_MAJOR_VERSION;
	start_req.host_version.minor_version = HBM_MINOR_VERSION;

	/*
	 * (!) Response to HBM start may be so quick that this thread would get
	 * preempted BEFORE managing to set hbm_state = ISHTP_HBM_START.
	 * So set it at first, change back to ISHTP_HBM_IDLE upon failure
	 */
	dev->hbm_state = ISHTP_HBM_START;
	if (ishtp_write_message(dev, &hdr, &start_req)) {
		dev_err(dev->devc, "version message send failed\n");
		dev->dev_state = ISHTP_DEV_RESETTING;
		dev->hbm_state = ISHTP_HBM_IDLE;
		ish_hw_reset(dev);
		return -ENODEV;
	}

	return 0;
}