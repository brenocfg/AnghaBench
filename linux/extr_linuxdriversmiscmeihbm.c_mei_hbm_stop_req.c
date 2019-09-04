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
struct mei_device {int dummy; } ;
struct hbm_host_stop_request {int /*<<< orphan*/  reason; int /*<<< orphan*/  hbm_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_STOP_REQUEST ; 
 int /*<<< orphan*/  HOST_STOP_REQ_CMD ; 
 int /*<<< orphan*/  mei_hbm_hdr (struct mei_msg_hdr*,size_t const) ; 
 int mei_hbm_write_message (struct mei_device*,struct mei_msg_hdr*,struct hbm_host_stop_request*) ; 
 int /*<<< orphan*/  memset (struct hbm_host_stop_request*,int /*<<< orphan*/ ,size_t const) ; 

__attribute__((used)) static int mei_hbm_stop_req(struct mei_device *dev)
{
	struct mei_msg_hdr mei_hdr;
	struct hbm_host_stop_request req;
	const size_t len = sizeof(struct hbm_host_stop_request);

	mei_hbm_hdr(&mei_hdr, len);

	memset(&req, 0, len);
	req.hbm_cmd = HOST_STOP_REQ_CMD;
	req.reason = DRIVER_STOP_REQUEST;

	return mei_hbm_write_message(dev, &mei_hdr, &req);
}