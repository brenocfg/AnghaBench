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
struct ishtp_device {int dummy; } ;
struct hbm_host_stop_request {int /*<<< orphan*/  reason; int /*<<< orphan*/  hbm_cmd; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  stop_req ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_STOP_REQUEST ; 
 int /*<<< orphan*/  HOST_STOP_REQ_CMD ; 
 int /*<<< orphan*/  ishtp_hbm_hdr (struct ishtp_msg_hdr*,int) ; 
 int /*<<< orphan*/  ishtp_write_message (struct ishtp_device*,struct ishtp_msg_hdr*,struct hbm_host_stop_request*) ; 

__attribute__((used)) static void ishtp_hbm_stop_req(struct ishtp_device *dev)
{
	struct ishtp_msg_hdr hdr;
	struct hbm_host_stop_request stop_req = { 0 } ;

	ishtp_hbm_hdr(&hdr, sizeof(stop_req));

	stop_req.hbm_cmd = HOST_STOP_REQ_CMD;
	stop_req.reason = DRIVER_STOP_REQUEST;

	ishtp_write_message(dev, &hdr, &stop_req);
}