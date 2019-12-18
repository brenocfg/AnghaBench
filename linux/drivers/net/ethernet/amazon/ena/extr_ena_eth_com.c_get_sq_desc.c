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
struct ena_com_io_sq {scalar_t__ mem_queue_type; } ;

/* Variables and functions */
 scalar_t__ ENA_ADMIN_PLACEMENT_POLICY_DEV ; 
 void* get_sq_desc_llq (struct ena_com_io_sq*) ; 
 void* get_sq_desc_regular_queue (struct ena_com_io_sq*) ; 

__attribute__((used)) static void *get_sq_desc(struct ena_com_io_sq *io_sq)
{
	if (io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_DEV)
		return get_sq_desc_llq(io_sq);

	return get_sq_desc_regular_queue(io_sq);
}