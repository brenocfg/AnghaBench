#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ kva; } ;
struct bfa_msgq_rspq {int consumer_index; TYPE_1__ addr; int /*<<< orphan*/  depth; } ;
struct bfa_msgq {struct bfa_msgq_rspq rspq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_MSGQ_INDX_ADD (int,int,int /*<<< orphan*/ ) ; 
 int BFI_MSGQ_RSP_ENTRY_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

void
bfa_msgq_rsp_copy(struct bfa_msgq *msgq, u8 *buf, size_t buf_len)
{
	struct bfa_msgq_rspq *rspq = &msgq->rspq;
	size_t len = buf_len;
	size_t to_copy;
	int ci;
	u8 *src, *dst;

	ci = rspq->consumer_index;
	src = (u8 *)rspq->addr.kva;
	src += (ci * BFI_MSGQ_RSP_ENTRY_SIZE);
	dst = buf;

	while (len) {
		to_copy = (len < BFI_MSGQ_RSP_ENTRY_SIZE) ?
				len : BFI_MSGQ_RSP_ENTRY_SIZE;
		memcpy(dst, src, to_copy);
		len -= to_copy;
		dst += BFI_MSGQ_RSP_ENTRY_SIZE;
		BFA_MSGQ_INDX_ADD(ci, 1, rspq->depth);
		src = (u8 *)rspq->addr.kva;
		src += (ci * BFI_MSGQ_RSP_ENTRY_SIZE);
	}
}