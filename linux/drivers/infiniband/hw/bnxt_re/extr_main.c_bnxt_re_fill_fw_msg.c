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
struct bnxt_fw_msg {int msg_len; int resp_max_len; int timeout; void* resp; void* msg; } ;

/* Variables and functions */

__attribute__((used)) static void bnxt_re_fill_fw_msg(struct bnxt_fw_msg *fw_msg, void *msg,
				int msg_len, void *resp, int resp_max_len,
				int timeout)
{
	fw_msg->msg = msg;
	fw_msg->msg_len = msg_len;
	fw_msg->resp = resp;
	fw_msg->resp_max_len = resp_max_len;
	fw_msg->timeout = timeout;
}