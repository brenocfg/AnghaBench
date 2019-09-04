#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct npu_context {TYPE_2__* mm; scalar_t__ nmmu_flush; } ;
struct mmio_atsd_reg {int dummy; } ;
struct TYPE_3__ {unsigned long id; } ;
struct TYPE_4__ {TYPE_1__ context; } ;

/* Variables and functions */
 int NV_MAX_NPUS ; 
 int /*<<< orphan*/  acquire_atsd_reg (struct npu_context*,struct mmio_atsd_reg*) ; 
 int /*<<< orphan*/  flush_all_mm (TYPE_2__*) ; 
 int /*<<< orphan*/  mmio_invalidate_pid (struct mmio_atsd_reg*,unsigned long,int) ; 
 int /*<<< orphan*/  mmio_invalidate_va (struct mmio_atsd_reg*,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  mmio_invalidate_wait (struct mmio_atsd_reg*) ; 
 int /*<<< orphan*/  release_atsd_reg (struct mmio_atsd_reg*) ; 

__attribute__((used)) static void mmio_invalidate(struct npu_context *npu_context, int va,
			unsigned long address, bool flush)
{
	struct mmio_atsd_reg mmio_atsd_reg[NV_MAX_NPUS];
	unsigned long pid = npu_context->mm->context.id;

	if (npu_context->nmmu_flush)
		/*
		 * Unfortunately the nest mmu does not support flushing specific
		 * addresses so we have to flush the whole mm once before
		 * shooting down the GPU translation.
		 */
		flush_all_mm(npu_context->mm);

	/*
	 * Loop over all the NPUs this process is active on and launch
	 * an invalidate.
	 */
	acquire_atsd_reg(npu_context, mmio_atsd_reg);
	if (va)
		mmio_invalidate_va(mmio_atsd_reg, address, pid, flush);
	else
		mmio_invalidate_pid(mmio_atsd_reg, pid, flush);

	mmio_invalidate_wait(mmio_atsd_reg);
	if (flush) {
		/*
		 * The GPU requires two flush ATSDs to ensure all entries have
		 * been flushed. We use PID 0 as it will never be used for a
		 * process on the GPU.
		 */
		mmio_invalidate_pid(mmio_atsd_reg, 0, true);
		mmio_invalidate_wait(mmio_atsd_reg);
		mmio_invalidate_pid(mmio_atsd_reg, 0, true);
		mmio_invalidate_wait(mmio_atsd_reg);
	}
	release_atsd_reg(mmio_atsd_reg);
}