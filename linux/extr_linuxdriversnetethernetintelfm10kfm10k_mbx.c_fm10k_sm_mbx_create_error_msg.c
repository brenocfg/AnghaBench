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
struct fm10k_mbx_info {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
#define  FM10K_MBX_ERR_HEAD 132 
#define  FM10K_MBX_ERR_RSVD0 131 
#define  FM10K_MBX_ERR_SIZE 130 
#define  FM10K_MBX_ERR_SRC 129 
#define  FM10K_MBX_ERR_TAIL 128 
 int /*<<< orphan*/  fm10k_sm_mbx_create_connect_hdr (struct fm10k_mbx_info*,int) ; 
 int /*<<< orphan*/  fm10k_sm_mbx_process_error (struct fm10k_mbx_info*) ; 

__attribute__((used)) static void fm10k_sm_mbx_create_error_msg(struct fm10k_mbx_info *mbx, s32 err)
{
	/* only generate an error message for these types */
	switch (err) {
	case FM10K_MBX_ERR_TAIL:
	case FM10K_MBX_ERR_HEAD:
	case FM10K_MBX_ERR_SRC:
	case FM10K_MBX_ERR_SIZE:
	case FM10K_MBX_ERR_RSVD0:
		break;
	default:
		return;
	}

	/* process it as though we received an error, and send error reply */
	fm10k_sm_mbx_process_error(mbx);
	fm10k_sm_mbx_create_connect_hdr(mbx, 1);
}