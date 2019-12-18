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
struct fm10k_mbx_info {int mbx_hdr; int /*<<< orphan*/  head; int /*<<< orphan*/  remote; int /*<<< orphan*/  tail; int /*<<< orphan*/  mbx_lock; scalar_t__ tail_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_MBX_REQ ; 
 int FM10K_MSG_HDR_FIELD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_HEAD ; 
 int /*<<< orphan*/  SM_TAIL ; 
 int /*<<< orphan*/  SM_VER ; 

__attribute__((used)) static void fm10k_sm_mbx_create_data_hdr(struct fm10k_mbx_info *mbx)
{
	if (mbx->tail_len)
		mbx->mbx_lock |= FM10K_MBX_REQ;

	mbx->mbx_hdr = FM10K_MSG_HDR_FIELD_SET(mbx->tail, SM_TAIL) |
		       FM10K_MSG_HDR_FIELD_SET(mbx->remote, SM_VER) |
		       FM10K_MSG_HDR_FIELD_SET(mbx->head, SM_HEAD);
}