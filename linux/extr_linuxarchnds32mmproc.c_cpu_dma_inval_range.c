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
struct TYPE_2__ {unsigned long line_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCTL_CMD_L2_PA_INVAL ; 
 int /*<<< orphan*/  CCTL_CMD_L2_PA_WBINVAL ; 
 size_t DCACHE ; 
 TYPE_1__* L1_cache_info ; 
 int /*<<< orphan*/  __nds32__msync_all () ; 
 int /*<<< orphan*/  cpu_dcache_inval_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  cpu_dcache_wbinval_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  cpu_l2cache_op (unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ unlikely (int) ; 

void cpu_dma_inval_range(unsigned long start, unsigned long end)
{
	unsigned long line_size;
	unsigned long old_start = start;
	unsigned long old_end = end;
	unsigned long flags;
	line_size = L1_cache_info[DCACHE].line_size;
	start = start & (~(line_size - 1));
	end = (end + line_size - 1) & (~(line_size - 1));
	if (unlikely(start == end))
		return;
	local_irq_save(flags);
	if (start != old_start) {
		cpu_dcache_wbinval_range(start, start + line_size);
		cpu_l2cache_op(start, start + line_size, CCTL_CMD_L2_PA_WBINVAL);
	}
	if (end != old_end) {
		cpu_dcache_wbinval_range(end - line_size, end);
		cpu_l2cache_op(end - line_size, end, CCTL_CMD_L2_PA_WBINVAL);
	}
	cpu_dcache_inval_range(start, end);
	cpu_l2cache_op(start, end, CCTL_CMD_L2_PA_INVAL);
	__nds32__msync_all();
	local_irq_restore(flags);

}