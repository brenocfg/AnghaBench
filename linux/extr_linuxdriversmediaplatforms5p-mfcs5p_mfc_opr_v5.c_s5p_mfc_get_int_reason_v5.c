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
struct s5p_mfc_dev {int dummy; } ;

/* Variables and functions */
#define  S5P_FIMV_R2H_CMD_CLOSE_INSTANCE_RET 139 
#define  S5P_FIMV_R2H_CMD_ENC_COMPLETE_RET 138 
#define  S5P_FIMV_R2H_CMD_ERR_RET 137 
#define  S5P_FIMV_R2H_CMD_FRAME_DONE_RET 136 
#define  S5P_FIMV_R2H_CMD_FW_STATUS_RET 135 
#define  S5P_FIMV_R2H_CMD_INIT_BUFFERS_RET 134 
#define  S5P_FIMV_R2H_CMD_OPEN_INSTANCE_RET 133 
#define  S5P_FIMV_R2H_CMD_SEQ_DONE_RET 132 
#define  S5P_FIMV_R2H_CMD_SLEEP_RET 131 
#define  S5P_FIMV_R2H_CMD_SLICE_DONE_RET 130 
#define  S5P_FIMV_R2H_CMD_SYS_INIT_RET 129 
#define  S5P_FIMV_R2H_CMD_WAKEUP_RET 128 
 int /*<<< orphan*/  S5P_FIMV_RISC2HOST_CMD ; 
 int S5P_FIMV_RISC2HOST_CMD_MASK ; 
 int S5P_MFC_R2H_CMD_CLOSE_INSTANCE_RET ; 
 int S5P_MFC_R2H_CMD_COMPLETE_SEQ_RET ; 
 int S5P_MFC_R2H_CMD_EMPTY ; 
 int S5P_MFC_R2H_CMD_ERR_RET ; 
 int S5P_MFC_R2H_CMD_FRAME_DONE_RET ; 
 int S5P_MFC_R2H_CMD_FW_STATUS_RET ; 
 int S5P_MFC_R2H_CMD_INIT_BUFFERS_RET ; 
 int S5P_MFC_R2H_CMD_OPEN_INSTANCE_RET ; 
 int S5P_MFC_R2H_CMD_SEQ_DONE_RET ; 
 int S5P_MFC_R2H_CMD_SLEEP_RET ; 
 int S5P_MFC_R2H_CMD_SLICE_DONE_RET ; 
 int S5P_MFC_R2H_CMD_SYS_INIT_RET ; 
 int S5P_MFC_R2H_CMD_WAKEUP_RET ; 
 int mfc_read (struct s5p_mfc_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_mfc_get_int_reason_v5(struct s5p_mfc_dev *dev)
{
	int reason;
	reason = mfc_read(dev, S5P_FIMV_RISC2HOST_CMD) &
		S5P_FIMV_RISC2HOST_CMD_MASK;
	switch (reason) {
	case S5P_FIMV_R2H_CMD_OPEN_INSTANCE_RET:
		reason = S5P_MFC_R2H_CMD_OPEN_INSTANCE_RET;
		break;
	case S5P_FIMV_R2H_CMD_CLOSE_INSTANCE_RET:
		reason = S5P_MFC_R2H_CMD_CLOSE_INSTANCE_RET;
		break;
	case S5P_FIMV_R2H_CMD_SEQ_DONE_RET:
		reason = S5P_MFC_R2H_CMD_SEQ_DONE_RET;
		break;
	case S5P_FIMV_R2H_CMD_FRAME_DONE_RET:
		reason = S5P_MFC_R2H_CMD_FRAME_DONE_RET;
		break;
	case S5P_FIMV_R2H_CMD_SLICE_DONE_RET:
		reason = S5P_MFC_R2H_CMD_SLICE_DONE_RET;
		break;
	case S5P_FIMV_R2H_CMD_SYS_INIT_RET:
		reason = S5P_MFC_R2H_CMD_SYS_INIT_RET;
		break;
	case S5P_FIMV_R2H_CMD_FW_STATUS_RET:
		reason = S5P_MFC_R2H_CMD_FW_STATUS_RET;
		break;
	case S5P_FIMV_R2H_CMD_SLEEP_RET:
		reason = S5P_MFC_R2H_CMD_SLEEP_RET;
		break;
	case S5P_FIMV_R2H_CMD_WAKEUP_RET:
		reason = S5P_MFC_R2H_CMD_WAKEUP_RET;
		break;
	case S5P_FIMV_R2H_CMD_INIT_BUFFERS_RET:
		reason = S5P_MFC_R2H_CMD_INIT_BUFFERS_RET;
		break;
	case S5P_FIMV_R2H_CMD_ENC_COMPLETE_RET:
		reason = S5P_MFC_R2H_CMD_COMPLETE_SEQ_RET;
		break;
	case S5P_FIMV_R2H_CMD_ERR_RET:
		reason = S5P_MFC_R2H_CMD_ERR_RET;
		break;
	default:
		reason = S5P_MFC_R2H_CMD_EMPTY;
	}
	return reason;
}