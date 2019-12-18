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
typedef  int u8 ;
struct scsi_cmnd {int result; } ;
struct response_iu {int response_code; } ;

/* Variables and functions */
 int DID_BAD_TARGET ; 
 int DID_ERROR ; 
 int DID_OK ; 
 int DID_TARGET_FAILURE ; 
#define  RC_INCORRECT_LUN 130 
#define  RC_TMF_NOT_SUPPORTED 129 
#define  RC_TMF_SUCCEEDED 128 
 int /*<<< orphan*/  uas_log_cmd_state (struct scsi_cmnd*,char*,int) ; 

__attribute__((used)) static bool uas_evaluate_response_iu(struct response_iu *riu, struct scsi_cmnd *cmnd)
{
	u8 response_code = riu->response_code;

	switch (response_code) {
	case RC_INCORRECT_LUN:
		cmnd->result = DID_BAD_TARGET << 16;
		break;
	case RC_TMF_SUCCEEDED:
		cmnd->result = DID_OK << 16;
		break;
	case RC_TMF_NOT_SUPPORTED:
		cmnd->result = DID_TARGET_FAILURE << 16;
		break;
	default:
		uas_log_cmd_state(cmnd, "response iu", response_code);
		cmnd->result = DID_ERROR << 16;
		break;
	}

	return response_code == RC_TMF_SUCCEEDED;
}