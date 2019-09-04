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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int pbuf_dev_addr; int virt_addr; } ;
struct ena_com_io_sq {int tail; int q_depth; int desc_entry_size; scalar_t__ mem_queue_type; TYPE_1__ desc_addr; } ;

/* Variables and functions */
 scalar_t__ ENA_ADMIN_PLACEMENT_POLICY_HOST ; 
 int /*<<< orphan*/  memcpy_toio (int,int,int) ; 

__attribute__((used)) static inline void ena_com_copy_curr_sq_desc_to_dev(struct ena_com_io_sq *io_sq)
{
	u16 tail_masked = io_sq->tail & (io_sq->q_depth - 1);
	u32 offset = tail_masked * io_sq->desc_entry_size;

	/* In case this queue isn't a LLQ */
	if (io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_HOST)
		return;

	memcpy_toio(io_sq->desc_addr.pbuf_dev_addr + offset,
		    io_sq->desc_addr.virt_addr + offset,
		    io_sq->desc_entry_size);
}