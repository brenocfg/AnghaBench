#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ length; int code; } ;
union fjes_device_command_res {TYPE_2__ stop_trace; } ;
union fjes_device_command_req {TYPE_2__ stop_trace; } ;
struct TYPE_3__ {int /*<<< orphan*/  res_buf_size; int /*<<< orphan*/  req_buf_size; int /*<<< orphan*/  trace; union fjes_device_command_res* res_buf; union fjes_device_command_res* req_buf; } ;
struct fjes_hw {int /*<<< orphan*/  debug_mode; TYPE_1__ hw_info; } ;
typedef  enum fjes_dev_command_response_e { ____Placeholder_fjes_dev_command_response_e } fjes_dev_command_response_e ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMSG ; 
 int EPERM ; 
#define  FJES_CMD_REQ_RES_CODE_NORMAL 132 
 int /*<<< orphan*/  FJES_CMD_REQ_STOP_DEBUG ; 
#define  FJES_CMD_STATUS_ERROR_PARAM 131 
#define  FJES_CMD_STATUS_ERROR_STATUS 130 
 int FJES_CMD_STATUS_NORMAL ; 
#define  FJES_CMD_STATUS_TIMEOUT 129 
#define  FJES_CMD_STATUS_UNKNOWN 128 
 scalar_t__ FJES_DEV_COMMAND_STOP_DBG_REQ_LEN ; 
 scalar_t__ FJES_DEV_COMMAND_STOP_DBG_RES_LEN ; 
 int fjes_hw_issue_request_command (struct fjes_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union fjes_device_command_res*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_fjes_hw_stop_debug (union fjes_device_command_res*) ; 
 int /*<<< orphan*/  trace_fjes_hw_stop_debug_err (char*) ; 

int fjes_hw_stop_debug(struct fjes_hw *hw)
{
	union fjes_device_command_req *req_buf = hw->hw_info.req_buf;
	union fjes_device_command_res *res_buf = hw->hw_info.res_buf;
	enum fjes_dev_command_response_e ret;
	int result = 0;

	if (!hw->hw_info.trace)
		return -EPERM;

	memset(req_buf, 0, hw->hw_info.req_buf_size);
	memset(res_buf, 0, hw->hw_info.res_buf_size);
	req_buf->stop_trace.length = FJES_DEV_COMMAND_STOP_DBG_REQ_LEN;

	res_buf->stop_trace.length = 0;
	res_buf->stop_trace.code = 0;

	ret = fjes_hw_issue_request_command(hw, FJES_CMD_REQ_STOP_DEBUG);
	trace_fjes_hw_stop_debug(res_buf);

	if (res_buf->stop_trace.length != FJES_DEV_COMMAND_STOP_DBG_RES_LEN) {
		trace_fjes_hw_stop_debug_err("Invalid res_buf");
		result = -ENOMSG;
	} else if (ret == FJES_CMD_STATUS_NORMAL) {
		switch (res_buf->stop_trace.code) {
		case FJES_CMD_REQ_RES_CODE_NORMAL:
			result = 0;
			hw->debug_mode = 0;
			break;
		default:
			result = -EPERM;
			break;
		}
	} else {
		switch (ret) {
		case FJES_CMD_STATUS_UNKNOWN:
			result = -EPERM;
			break;
		case FJES_CMD_STATUS_TIMEOUT:
			result = -EBUSY;
			trace_fjes_hw_stop_debug_err("Busy Timeout");
			break;
		case FJES_CMD_STATUS_ERROR_PARAM:
		case FJES_CMD_STATUS_ERROR_STATUS:
		default:
			result = -EPERM;
			break;
		}
	}

	return result;
}