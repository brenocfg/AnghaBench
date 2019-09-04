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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/ * buffer; } ;
struct fm10k_mbx_info {int /*<<< orphan*/  pushed; TYPE_1__ rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_TLV_DWORD_LEN (int /*<<< orphan*/ ) ; 
 int fm10k_fifo_tail_offset (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 fm10k_mbx_pushed_tail_len(struct fm10k_mbx_info *mbx)
{
	u32 *tail = mbx->rx.buffer + fm10k_fifo_tail_offset(&mbx->rx, 0);

	/* pushed tail is only valid if pushed is set */
	if (!mbx->pushed)
		return 0;

	return FM10K_TLV_DWORD_LEN(*tail);
}