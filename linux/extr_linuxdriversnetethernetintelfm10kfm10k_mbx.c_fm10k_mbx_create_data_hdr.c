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
struct fm10k_mbx_fifo {int dummy; } ;
struct fm10k_mbx_info {int mbx_hdr; int /*<<< orphan*/  local; int /*<<< orphan*/  tail_len; int /*<<< orphan*/  pulled; int /*<<< orphan*/  mbx_lock; struct fm10k_mbx_fifo tx; int /*<<< orphan*/  head; int /*<<< orphan*/  tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRC ; 
 int /*<<< orphan*/  FM10K_MBX_REQ ; 
 int /*<<< orphan*/  FM10K_MSG_DATA ; 
 int FM10K_MSG_HDR_FIELD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEAD ; 
 int /*<<< orphan*/  TAIL ; 
 int /*<<< orphan*/  TYPE ; 
 int /*<<< orphan*/  fm10k_crc_16b (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fm10k_fifo_crc (struct fm10k_mbx_fifo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_fifo_head_offset (struct fm10k_mbx_fifo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_mbx_create_data_hdr(struct fm10k_mbx_info *mbx)
{
	u32 hdr = FM10K_MSG_HDR_FIELD_SET(FM10K_MSG_DATA, TYPE) |
		  FM10K_MSG_HDR_FIELD_SET(mbx->tail, TAIL) |
		  FM10K_MSG_HDR_FIELD_SET(mbx->head, HEAD);
	struct fm10k_mbx_fifo *fifo = &mbx->tx;
	u16 crc;

	if (mbx->tail_len)
		mbx->mbx_lock |= FM10K_MBX_REQ;

	/* generate CRC for data in flight and header */
	crc = fm10k_fifo_crc(fifo, fm10k_fifo_head_offset(fifo, mbx->pulled),
			     mbx->tail_len, mbx->local);
	crc = fm10k_crc_16b(&hdr, crc, 1);

	/* load header to memory to be written */
	mbx->mbx_hdr = hdr | FM10K_MSG_HDR_FIELD_SET(crc, CRC);
}