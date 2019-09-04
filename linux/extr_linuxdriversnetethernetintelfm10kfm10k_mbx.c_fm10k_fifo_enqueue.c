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
typedef  scalar_t__ u16 ;
struct fm10k_mbx_fifo {scalar_t__ size; int /*<<< orphan*/  tail; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_MBX_ERR_NO_SPACE ; 
 int /*<<< orphan*/  FM10K_MBX_ERR_SIZE ; 
 scalar_t__ FM10K_TLV_DWORD_LEN (int /*<<< orphan*/  const) ; 
 scalar_t__ fm10k_fifo_unused (struct fm10k_mbx_fifo*) ; 
 int /*<<< orphan*/  fm10k_fifo_write_copy (struct fm10k_mbx_fifo*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static s32 fm10k_fifo_enqueue(struct fm10k_mbx_fifo *fifo, const u32 *msg)
{
	u16 len = FM10K_TLV_DWORD_LEN(*msg);

	/* verify parameters */
	if (len > fifo->size)
		return FM10K_MBX_ERR_SIZE;

	/* verify there is room for the message */
	if (len > fm10k_fifo_unused(fifo))
		return FM10K_MBX_ERR_NO_SPACE;

	/* Copy message into FIFO */
	fm10k_fifo_write_copy(fifo, msg, 0, len);

	/* memory barrier to guarantee FIFO is written before tail update */
	wmb();

	/* Update Tx FIFO tail */
	fifo->tail += len;

	return 0;
}