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
typedef  scalar_t__ u16 ;
struct fm10k_mbx_fifo {int dummy; } ;
struct fm10k_mbx_info {int /*<<< orphan*/  remote; int /*<<< orphan*/  mbx_hdr; int /*<<< orphan*/  pushed; scalar_t__ head_len; struct fm10k_mbx_fifo rx; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_MBX_ERR_CRC ; 
 scalar_t__ fm10k_crc_16b (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fm10k_fifo_crc (struct fm10k_mbx_fifo*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ fm10k_fifo_tail_offset (struct fm10k_mbx_fifo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 fm10k_mbx_verify_remote_crc(struct fm10k_mbx_info *mbx)
{
	struct fm10k_mbx_fifo *fifo = &mbx->rx;
	u16 len = mbx->head_len;
	u16 offset = fm10k_fifo_tail_offset(fifo, mbx->pushed) - len;
	u16 crc;

	/* update the remote CRC if new data has been received */
	if (len)
		mbx->remote = fm10k_fifo_crc(fifo, offset, len, mbx->remote);

	/* process the full header as we have to validate the CRC */
	crc = fm10k_crc_16b(&mbx->mbx_hdr, mbx->remote, 1);

	/* notify other end if we have a problem */
	return crc ? FM10K_MBX_ERR_CRC : 0;
}