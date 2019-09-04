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
struct fm10k_mbx_info {int head; int tail; int /*<<< orphan*/  mbmem_len; int /*<<< orphan*/  tail_len; int /*<<< orphan*/  mbx_hdr; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECT_SIZE ; 
 int /*<<< orphan*/  FM10K_MBX_ERR_HEAD ; 
 int /*<<< orphan*/  FM10K_MBX_ERR_RSVD0 ; 
 int /*<<< orphan*/  FM10K_MBX_ERR_SIZE ; 
 int /*<<< orphan*/  FM10K_MBX_ERR_TAIL ; 
 int /*<<< orphan*/  FM10K_MBX_ERR_TYPE ; 
#define  FM10K_MSG_CONNECT 131 
#define  FM10K_MSG_DATA 130 
#define  FM10K_MSG_DISCONNECT 129 
#define  FM10K_MSG_ERROR 128 
 int FM10K_MSG_HDR_FIELD_GET (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int FM10K_MSG_HDR_MASK (int /*<<< orphan*/ ) ; 
 int FM10K_VFMBX_MSG_MTU ; 
 int /*<<< orphan*/  HEAD ; 
 int /*<<< orphan*/  RSVD0 ; 
 int /*<<< orphan*/  TAIL ; 
 int /*<<< orphan*/  TYPE ; 
 int /*<<< orphan*/  fm10k_mbx_index_len (struct fm10k_mbx_info*,int,int) ; 

__attribute__((used)) static s32 fm10k_mbx_validate_msg_hdr(struct fm10k_mbx_info *mbx)
{
	u16 type, rsvd0, head, tail, size;
	const u32 *hdr = &mbx->mbx_hdr;

	type = FM10K_MSG_HDR_FIELD_GET(*hdr, TYPE);
	rsvd0 = FM10K_MSG_HDR_FIELD_GET(*hdr, RSVD0);
	tail = FM10K_MSG_HDR_FIELD_GET(*hdr, TAIL);
	head = FM10K_MSG_HDR_FIELD_GET(*hdr, HEAD);
	size = FM10K_MSG_HDR_FIELD_GET(*hdr, CONNECT_SIZE);

	if (rsvd0)
		return FM10K_MBX_ERR_RSVD0;

	switch (type) {
	case FM10K_MSG_DISCONNECT:
		/* validate that all data has been received */
		if (tail != mbx->head)
			return FM10K_MBX_ERR_TAIL;

		/* fall through */
	case FM10K_MSG_DATA:
		/* validate that head is moving correctly */
		if (!head || (head == FM10K_MSG_HDR_MASK(HEAD)))
			return FM10K_MBX_ERR_HEAD;
		if (fm10k_mbx_index_len(mbx, head, mbx->tail) > mbx->tail_len)
			return FM10K_MBX_ERR_HEAD;

		/* validate that tail is moving correctly */
		if (!tail || (tail == FM10K_MSG_HDR_MASK(TAIL)))
			return FM10K_MBX_ERR_TAIL;
		if (fm10k_mbx_index_len(mbx, mbx->head, tail) < mbx->mbmem_len)
			break;

		return FM10K_MBX_ERR_TAIL;
	case FM10K_MSG_CONNECT:
		/* validate size is in range and is power of 2 mask */
		if ((size < FM10K_VFMBX_MSG_MTU) || (size & (size + 1)))
			return FM10K_MBX_ERR_SIZE;

		/* fall through */
	case FM10K_MSG_ERROR:
		if (!head || (head == FM10K_MSG_HDR_MASK(HEAD)))
			return FM10K_MBX_ERR_HEAD;
		/* neither create nor error include a tail offset */
		if (tail)
			return FM10K_MBX_ERR_TAIL;

		break;
	default:
		return FM10K_MBX_ERR_TYPE;
	}

	return 0;
}