#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ length; int epid; int* buffer; int code; } ;
union fjes_device_command_res {TYPE_3__ share_buffer; } ;
union fjes_device_command_req {TYPE_3__ share_buffer; } ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_8__ {int /*<<< orphan*/  buffer_share_bit; int /*<<< orphan*/  res_buf_size; int /*<<< orphan*/  req_buf_size; union fjes_device_command_res* res_buf; union fjes_device_command_res* req_buf; } ;
struct fjes_hw {int my_epid; TYPE_4__ hw_info; } ;
struct TYPE_6__ {int size; scalar_t__ buffer; } ;
struct TYPE_5__ {int size; scalar_t__ buffer; } ;
struct ep_share_mem_info {TYPE_2__ rx; TYPE_1__ tx; } ;
typedef  enum fjes_dev_command_response_e { ____Placeholder_fjes_dev_command_response_e } fjes_dev_command_response_e ;
typedef  void* __le64 ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMSG ; 
 int EPERM ; 
 int EP_BUFFER_INFO_SIZE ; 
#define  FJES_CMD_REQ_RES_CODE_BUSY 133 
#define  FJES_CMD_REQ_RES_CODE_NORMAL 132 
 int /*<<< orphan*/  FJES_CMD_REQ_SHARE_BUFFER ; 
#define  FJES_CMD_STATUS_ERROR_PARAM 131 
#define  FJES_CMD_STATUS_ERROR_STATUS 130 
 int FJES_CMD_STATUS_NORMAL ; 
#define  FJES_CMD_STATUS_TIMEOUT 129 
#define  FJES_CMD_STATUS_UNKNOWN 128 
 int FJES_COMMAND_REQ_BUFF_TIMEOUT ; 
 scalar_t__ FJES_DEV_COMMAND_SHARE_BUFFER_REQ_LEN (int,int) ; 
 scalar_t__ FJES_DEV_COMMAND_SHARE_BUFFER_RES_LEN ; 
 int fjes_hw_issue_request_command (struct fjes_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union fjes_device_command_res*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ offset_in_page (void*) ; 
 scalar_t__ page_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_fjes_hw_register_buff_addr (union fjes_device_command_res*,int) ; 
 int /*<<< orphan*/  trace_fjes_hw_register_buff_addr_err (char*) ; 
 int /*<<< orphan*/  trace_fjes_hw_register_buff_addr_req (union fjes_device_command_res*,struct ep_share_mem_info*) ; 
 int /*<<< orphan*/  vmalloc_to_page (void*) ; 

int fjes_hw_register_buff_addr(struct fjes_hw *hw, int dest_epid,
			       struct ep_share_mem_info *buf_pair)
{
	union fjes_device_command_req *req_buf = hw->hw_info.req_buf;
	union fjes_device_command_res *res_buf = hw->hw_info.res_buf;
	enum fjes_dev_command_response_e ret;
	int page_count;
	int timeout;
	int i, idx;
	void *addr;
	int result;

	if (test_bit(dest_epid, &hw->hw_info.buffer_share_bit))
		return 0;

	memset(req_buf, 0, hw->hw_info.req_buf_size);
	memset(res_buf, 0, hw->hw_info.res_buf_size);

	req_buf->share_buffer.length = FJES_DEV_COMMAND_SHARE_BUFFER_REQ_LEN(
						buf_pair->tx.size,
						buf_pair->rx.size);
	req_buf->share_buffer.epid = dest_epid;

	idx = 0;
	req_buf->share_buffer.buffer[idx++] = buf_pair->tx.size;
	page_count = buf_pair->tx.size / EP_BUFFER_INFO_SIZE;
	for (i = 0; i < page_count; i++) {
		addr = ((u8 *)(buf_pair->tx.buffer)) +
				(i * EP_BUFFER_INFO_SIZE);
		req_buf->share_buffer.buffer[idx++] =
				(__le64)(page_to_phys(vmalloc_to_page(addr)) +
						offset_in_page(addr));
	}

	req_buf->share_buffer.buffer[idx++] = buf_pair->rx.size;
	page_count = buf_pair->rx.size / EP_BUFFER_INFO_SIZE;
	for (i = 0; i < page_count; i++) {
		addr = ((u8 *)(buf_pair->rx.buffer)) +
				(i * EP_BUFFER_INFO_SIZE);
		req_buf->share_buffer.buffer[idx++] =
				(__le64)(page_to_phys(vmalloc_to_page(addr)) +
						offset_in_page(addr));
	}

	res_buf->share_buffer.length = 0;
	res_buf->share_buffer.code = 0;

	trace_fjes_hw_register_buff_addr_req(req_buf, buf_pair);

	ret = fjes_hw_issue_request_command(hw, FJES_CMD_REQ_SHARE_BUFFER);

	timeout = FJES_COMMAND_REQ_BUFF_TIMEOUT * 1000;
	while ((ret == FJES_CMD_STATUS_NORMAL) &&
	       (res_buf->share_buffer.length ==
		FJES_DEV_COMMAND_SHARE_BUFFER_RES_LEN) &&
	       (res_buf->share_buffer.code == FJES_CMD_REQ_RES_CODE_BUSY) &&
	       (timeout > 0)) {
			msleep(200 + hw->my_epid * 20);
			timeout -= (200 + hw->my_epid * 20);

			res_buf->share_buffer.length = 0;
			res_buf->share_buffer.code = 0;

			ret = fjes_hw_issue_request_command(
					hw, FJES_CMD_REQ_SHARE_BUFFER);
	}

	result = 0;

	trace_fjes_hw_register_buff_addr(res_buf, timeout);

	if (res_buf->share_buffer.length !=
			FJES_DEV_COMMAND_SHARE_BUFFER_RES_LEN) {
		trace_fjes_hw_register_buff_addr_err("Invalid res_buf");
		result = -ENOMSG;
	} else if (ret == FJES_CMD_STATUS_NORMAL) {
		switch (res_buf->share_buffer.code) {
		case FJES_CMD_REQ_RES_CODE_NORMAL:
			result = 0;
			set_bit(dest_epid, &hw->hw_info.buffer_share_bit);
			break;
		case FJES_CMD_REQ_RES_CODE_BUSY:
			trace_fjes_hw_register_buff_addr_err("Busy Timeout");
			result = -EBUSY;
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
			trace_fjes_hw_register_buff_addr_err("Timeout");
			result = -EBUSY;
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