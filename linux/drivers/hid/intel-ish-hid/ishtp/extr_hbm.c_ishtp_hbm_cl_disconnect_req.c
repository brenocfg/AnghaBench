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
struct ishtp_cl {int dummy; } ;
struct hbm_client_connect_request {int dummy; } ;
typedef  int /*<<< orphan*/  disconn_req ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_DISCONNECT_REQ_CMD ; 
 int /*<<< orphan*/  ishtp_hbm_cl_hdr (struct ishtp_cl*,int /*<<< orphan*/ ,struct hbm_client_connect_request*,size_t const) ; 
 int /*<<< orphan*/  ishtp_hbm_hdr (struct ishtp_msg_hdr*,size_t const) ; 
 int ishtp_write_message (struct ishtp_device*,struct ishtp_msg_hdr*,struct hbm_client_connect_request*) ; 

int ishtp_hbm_cl_disconnect_req(struct ishtp_device *dev, struct ishtp_cl *cl)
{
	struct ishtp_msg_hdr hdr;
	struct hbm_client_connect_request disconn_req;
	const size_t len = sizeof(disconn_req);

	ishtp_hbm_hdr(&hdr, len);
	ishtp_hbm_cl_hdr(cl, CLIENT_DISCONNECT_REQ_CMD, &disconn_req, len);

	return ishtp_write_message(dev, &hdr, &disconn_req);
}