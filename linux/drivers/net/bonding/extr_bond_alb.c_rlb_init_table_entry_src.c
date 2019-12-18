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
struct rlb_client_info {void* src_next; void* src_prev; void* src_first; } ;

/* Variables and functions */
 void* RLB_NULL_INDEX ; 

__attribute__((used)) static void rlb_init_table_entry_src(struct rlb_client_info *entry)
{
	entry->src_first = RLB_NULL_INDEX;
	entry->src_prev = RLB_NULL_INDEX;
	entry->src_next = RLB_NULL_INDEX;
}