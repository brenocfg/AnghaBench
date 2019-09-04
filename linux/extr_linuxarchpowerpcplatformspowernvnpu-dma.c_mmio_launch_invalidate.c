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
struct npu {scalar_t__* mmio_atsd_regs; } ;
struct mmio_atsd_reg {int reg; struct npu* npu; } ;

/* Variables and functions */
 scalar_t__ XTS_ATSD_AVA ; 
 int /*<<< orphan*/  __raw_writeq_be (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  eieio () ; 

__attribute__((used)) static void mmio_launch_invalidate(struct mmio_atsd_reg *mmio_atsd_reg,
				unsigned long launch, unsigned long va)
{
	struct npu *npu = mmio_atsd_reg->npu;
	int reg = mmio_atsd_reg->reg;

	__raw_writeq_be(va, npu->mmio_atsd_regs[reg] + XTS_ATSD_AVA);
	eieio();
	__raw_writeq_be(launch, npu->mmio_atsd_regs[reg]);
}