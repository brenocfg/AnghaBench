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
 int FM10K_MSG_HDR_FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  FM10K_SM_MBX_VERSION 128 
 scalar_t__ FM10K_STATE_CLOSED ; 
 int /*<<< orphan*/  SM_ERR ; 
 int /*<<< orphan*/  SM_VER ; 
 scalar_t__ fm10k_mbx_read (struct fm10k_hw*,struct fm10k_mbx_info*) ; 
 int /*<<< orphan*/  fm10k_mbx_write (struct fm10k_hw*,struct fm10k_mbx_info*) ; 
 int /*<<< orphan*/  fm10k_sm_mbx_create_error_msg (struct fm10k_mbx_info*,scalar_t__) ; 
 int /*<<< orphan*/  fm10k_sm_mbx_process_error (struct fm10k_mbx_info*) ; 
 scalar_t__ fm10k_sm_mbx_process_reset (struct fm10k_hw*,struct fm10k_mbx_info*) ; 
 scalar_t__ fm10k_sm_mbx_process_version_1 (struct fm10k_hw*,struct fm10k_mbx_info*) ; 
 scalar_t__ fm10k_sm_mbx_validate_fifo_hdr (struct fm10k_mbx_info*) ; 

__attribute__((used)) static s32 fm10k_sm_mbx_process(struct fm10k_hw *hw,
				struct fm10k_mbx_info *mbx)
{
	s32 err;

	/* we do not read mailbox if closed */
	if (mbx->state == FM10K_STATE_CLOSED)
		return 0;

	/* retrieve data from switch manager */
	err = fm10k_mbx_read(hw, mbx);
	if (err)
		return err;

	err = fm10k_sm_mbx_validate_fifo_hdr(mbx);
	if (err < 0)
		goto fifo_err;

	if (FM10K_MSG_HDR_FIELD_GET(mbx->mbx_hdr, SM_ERR)) {
		fm10k_sm_mbx_process_error(mbx);
		goto fifo_err;
	}

	switch (FM10K_MSG_HDR_FIELD_GET(mbx->mbx_hdr, SM_VER)) {
	case 0:
		err = fm10k_sm_mbx_process_reset(hw, mbx);
		break;
	case FM10K_SM_MBX_VERSION:
		err = fm10k_sm_mbx_process_version_1(hw, mbx);
		break;
	}

fifo_err:
	if (err < 0)
		fm10k_sm_mbx_create_error_msg(mbx, err);

	/* report data to switch manager */
	fm10k_mbx_write(hw, mbx);

	return err;
}