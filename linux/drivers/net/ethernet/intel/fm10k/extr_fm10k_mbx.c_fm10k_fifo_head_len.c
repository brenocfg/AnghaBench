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
typedef  int /*<<< orphan*/  u16 ;
struct fm10k_mbx_fifo {int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_TLV_DWORD_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ fm10k_fifo_empty (struct fm10k_mbx_fifo*) ; 
 int fm10k_fifo_head_offset (struct fm10k_mbx_fifo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 fm10k_fifo_head_len(struct fm10k_mbx_fifo *fifo)
{
	u32 *head = fifo->buffer + fm10k_fifo_head_offset(fifo, 0);

	/* verify there is at least 1 DWORD in the fifo so *head is valid */
	if (fm10k_fifo_empty(fifo))
		return 0;

	/* retieve the message length */
	return FM10K_TLV_DWORD_LEN(*head);
}