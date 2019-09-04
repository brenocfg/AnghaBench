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
typedef  void* u32 ;
struct vsp1_dl_body {size_t num_entries; size_t max_entries; TYPE_1__* entries; } ;
struct TYPE_2__ {void* data; void* addr; } ;

/* Variables and functions */
 scalar_t__ WARN_ONCE (int,char*,size_t) ; 

void vsp1_dl_body_write(struct vsp1_dl_body *dlb, u32 reg, u32 data)
{
	if (WARN_ONCE(dlb->num_entries >= dlb->max_entries,
		      "DLB size exceeded (max %u)", dlb->max_entries))
		return;

	dlb->entries[dlb->num_entries].addr = reg;
	dlb->entries[dlb->num_entries].data = data;
	dlb->num_entries++;
}