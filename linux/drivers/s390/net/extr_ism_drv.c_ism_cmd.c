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
struct ism_resp_hdr {int ret; int len; } ;
struct ism_req_hdr {int len; } ;
struct ism_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISM_ERROR ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ism_read_cmd (struct ism_dev*,struct ism_resp_hdr*,int,int) ; 
 int /*<<< orphan*/  __ism_write_cmd (struct ism_dev*,struct ism_req_hdr*,int,int) ; 
 int /*<<< orphan*/  debug_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ism_resp_hdr*,int) ; 
 int /*<<< orphan*/  debug_text_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ism_debug_info ; 

__attribute__((used)) static int ism_cmd(struct ism_dev *ism, void *cmd)
{
	struct ism_req_hdr *req = cmd;
	struct ism_resp_hdr *resp = cmd;

	__ism_write_cmd(ism, req + 1, sizeof(*req), req->len - sizeof(*req));
	__ism_write_cmd(ism, req, 0, sizeof(*req));

	WRITE_ONCE(resp->ret, ISM_ERROR);

	__ism_read_cmd(ism, resp, 0, sizeof(*resp));
	if (resp->ret) {
		debug_text_event(ism_debug_info, 0, "cmd failure");
		debug_event(ism_debug_info, 0, resp, sizeof(*resp));
		goto out;
	}
	__ism_read_cmd(ism, resp + 1, sizeof(*resp), resp->len - sizeof(*resp));
out:
	return resp->ret;
}