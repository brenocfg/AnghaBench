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
typedef  size_t u8 ;
struct vub300_mmc_host {int total_offload_count; TYPE_1__* fn; } ;
struct offload_registers_access {int dummy; } ;
struct TYPE_2__ {size_t offload_point; size_t offload_count; int /*<<< orphan*/ * reg; } ;

/* Variables and functions */
 size_t MAXREGMASK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct offload_registers_access*,int) ; 

__attribute__((used)) static void __add_offloaded_reg_to_fifo(struct vub300_mmc_host *vub300,
					struct offload_registers_access
					*register_access, u8 func)
{
	u8 r = vub300->fn[func].offload_point + vub300->fn[func].offload_count;
	memcpy(&vub300->fn[func].reg[MAXREGMASK & r], register_access,
	       sizeof(struct offload_registers_access));
	vub300->fn[func].offload_count += 1;
	vub300->total_offload_count += 1;
}