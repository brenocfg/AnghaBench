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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct fm10k_mbx_info {int tail; int head; int /*<<< orphan*/  mbmem_len; int /*<<< orphan*/  tail_len; int /*<<< orphan*/  mbx_hdr; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_MBX_ERR_HEAD ; 
 int /*<<< orphan*/  FM10K_MBX_ERR_SRC ; 
 int /*<<< orphan*/  FM10K_MBX_ERR_TAIL ; 
 int FM10K_MSG_HDR_FIELD_GET (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int FM10K_SM_MBX_FIFO_LEN ; 
#define  FM10K_SM_MBX_VERSION 128 
 int /*<<< orphan*/  SM_HEAD ; 
 int /*<<< orphan*/  SM_TAIL ; 
 int /*<<< orphan*/  SM_VER ; 
 int /*<<< orphan*/  fm10k_mbx_index_len (struct fm10k_mbx_info*,int,int) ; 

__attribute__((used)) static s32 fm10k_sm_mbx_validate_fifo_hdr(struct fm10k_mbx_info *mbx)
{
	const u32 *hdr = &mbx->mbx_hdr;
	u16 tail, head, ver;

	tail = FM10K_MSG_HDR_FIELD_GET(*hdr, SM_TAIL);
	ver = FM10K_MSG_HDR_FIELD_GET(*hdr, SM_VER);
	head = FM10K_MSG_HDR_FIELD_GET(*hdr, SM_HEAD);

	switch (ver) {
	case 0:
		break;
	case FM10K_SM_MBX_VERSION:
		if (!head || head > FM10K_SM_MBX_FIFO_LEN)
			return FM10K_MBX_ERR_HEAD;
		if (!tail || tail > FM10K_SM_MBX_FIFO_LEN)
			return FM10K_MBX_ERR_TAIL;
		if (mbx->tail < head)
			head += mbx->mbmem_len - 1;
		if (tail < mbx->head)
			tail += mbx->mbmem_len - 1;
		if (fm10k_mbx_index_len(mbx, head, mbx->tail) > mbx->tail_len)
			return FM10K_MBX_ERR_HEAD;
		if (fm10k_mbx_index_len(mbx, mbx->head, tail) < mbx->mbmem_len)
			break;
		return FM10K_MBX_ERR_TAIL;
	default:
		return FM10K_MBX_ERR_SRC;
	}

	return 0;
}