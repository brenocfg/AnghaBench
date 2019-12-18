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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fm10k_mbx_info {int mbx_hdr; int /*<<< orphan*/  mbx_lock; int /*<<< orphan*/  local; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRC ; 
 int /*<<< orphan*/  FM10K_MBX_ACK ; 
 int /*<<< orphan*/  FM10K_MSG_DISCONNECT ; 
 int FM10K_MSG_HDR_FIELD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEAD ; 
 int /*<<< orphan*/  TAIL ; 
 int /*<<< orphan*/  TYPE ; 
 int /*<<< orphan*/  fm10k_crc_16b (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fm10k_mbx_create_fake_disconnect_hdr(struct fm10k_mbx_info *mbx)
{
	u32 hdr = FM10K_MSG_HDR_FIELD_SET(FM10K_MSG_DISCONNECT, TYPE) |
		  FM10K_MSG_HDR_FIELD_SET(mbx->head, TAIL) |
		  FM10K_MSG_HDR_FIELD_SET(mbx->tail, HEAD);
	u16 crc = fm10k_crc_16b(&hdr, mbx->local, 1);

	mbx->mbx_lock |= FM10K_MBX_ACK;

	/* load header to memory to be written */
	mbx->mbx_hdr = hdr | FM10K_MSG_HDR_FIELD_SET(crc, CRC);
}