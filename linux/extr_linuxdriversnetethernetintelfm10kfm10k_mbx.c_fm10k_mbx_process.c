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
struct fm10k_mbx_info {scalar_t__ state; int /*<<< orphan*/  mbx_hdr; } ;
struct fm10k_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ FM10K_MBX_ERR_TYPE ; 
#define  FM10K_MSG_CONNECT 131 
#define  FM10K_MSG_DATA 130 
#define  FM10K_MSG_DISCONNECT 129 
#define  FM10K_MSG_ERROR 128 
 int FM10K_MSG_HDR_FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FM10K_STATE_CLOSED ; 
 int /*<<< orphan*/  TYPE ; 
 int /*<<< orphan*/  fm10k_mbx_create_error_msg (struct fm10k_mbx_info*,scalar_t__) ; 
 scalar_t__ fm10k_mbx_process_connect (struct fm10k_hw*,struct fm10k_mbx_info*) ; 
 scalar_t__ fm10k_mbx_process_data (struct fm10k_hw*,struct fm10k_mbx_info*) ; 
 scalar_t__ fm10k_mbx_process_disconnect (struct fm10k_hw*,struct fm10k_mbx_info*) ; 
 scalar_t__ fm10k_mbx_process_error (struct fm10k_hw*,struct fm10k_mbx_info*) ; 
 scalar_t__ fm10k_mbx_read (struct fm10k_hw*,struct fm10k_mbx_info*) ; 
 scalar_t__ fm10k_mbx_validate_msg_hdr (struct fm10k_mbx_info*) ; 
 int /*<<< orphan*/  fm10k_mbx_write (struct fm10k_hw*,struct fm10k_mbx_info*) ; 

__attribute__((used)) static s32 fm10k_mbx_process(struct fm10k_hw *hw,
			     struct fm10k_mbx_info *mbx)
{
	s32 err;

	/* we do not read mailbox if closed */
	if (mbx->state == FM10K_STATE_CLOSED)
		return 0;

	/* copy data from mailbox */
	err = fm10k_mbx_read(hw, mbx);
	if (err)
		return err;

	/* validate type, source, and destination */
	err = fm10k_mbx_validate_msg_hdr(mbx);
	if (err < 0)
		goto msg_err;

	switch (FM10K_MSG_HDR_FIELD_GET(mbx->mbx_hdr, TYPE)) {
	case FM10K_MSG_CONNECT:
		err = fm10k_mbx_process_connect(hw, mbx);
		break;
	case FM10K_MSG_DATA:
		err = fm10k_mbx_process_data(hw, mbx);
		break;
	case FM10K_MSG_DISCONNECT:
		err = fm10k_mbx_process_disconnect(hw, mbx);
		break;
	case FM10K_MSG_ERROR:
		err = fm10k_mbx_process_error(hw, mbx);
		break;
	default:
		err = FM10K_MBX_ERR_TYPE;
		break;
	}

msg_err:
	/* notify partner of errors on our end */
	if (err < 0)
		fm10k_mbx_create_error_msg(mbx, err);

	/* copy data from mailbox */
	fm10k_mbx_write(hw, mbx);

	return err;
}