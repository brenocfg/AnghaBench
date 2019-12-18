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
struct fm10k_mbx_info {int mbx_hdr; int head; int /*<<< orphan*/  mbx_lock; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_NO ; 
#define  FM10K_MBX_ERR_CRC 133 
#define  FM10K_MBX_ERR_HEAD 132 
#define  FM10K_MBX_ERR_RSVD0 131 
#define  FM10K_MBX_ERR_SIZE 130 
#define  FM10K_MBX_ERR_TAIL 129 
#define  FM10K_MBX_ERR_TYPE 128 
 int /*<<< orphan*/  FM10K_MBX_REQ ; 
 int FM10K_MSG_ERROR ; 
 int FM10K_MSG_HDR_FIELD_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEAD ; 
 int /*<<< orphan*/  TYPE ; 

__attribute__((used)) static void fm10k_mbx_create_error_msg(struct fm10k_mbx_info *mbx, s32 err)
{
	/* only generate an error message for these types */
	switch (err) {
	case FM10K_MBX_ERR_TAIL:
	case FM10K_MBX_ERR_HEAD:
	case FM10K_MBX_ERR_TYPE:
	case FM10K_MBX_ERR_SIZE:
	case FM10K_MBX_ERR_RSVD0:
	case FM10K_MBX_ERR_CRC:
		break;
	default:
		return;
	}

	mbx->mbx_lock |= FM10K_MBX_REQ;

	mbx->mbx_hdr = FM10K_MSG_HDR_FIELD_SET(FM10K_MSG_ERROR, TYPE) |
		       FM10K_MSG_HDR_FIELD_SET(err, ERR_NO) |
		       FM10K_MSG_HDR_FIELD_SET(mbx->head, HEAD);
}