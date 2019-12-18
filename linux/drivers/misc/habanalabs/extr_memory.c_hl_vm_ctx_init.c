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
typedef  int /*<<< orphan*/  u64 ;
struct hl_ctx {TYPE_1__* hdev; int /*<<< orphan*/  dram_phys_mem; } ;
struct asic_fixed_properties {int /*<<< orphan*/  dram_end_address; int /*<<< orphan*/  dram_user_base_address; int /*<<< orphan*/  va_space_host_end_address; int /*<<< orphan*/  va_space_host_start_address; int /*<<< orphan*/  va_space_dram_end_address; int /*<<< orphan*/  va_space_dram_start_address; } ;
struct TYPE_2__ {scalar_t__ mmu_enable; struct asic_fixed_properties asic_prop; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hl_vm_ctx_init_with_ranges (struct hl_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hl_vm_ctx_init(struct hl_ctx *ctx)
{
	struct asic_fixed_properties *prop = &ctx->hdev->asic_prop;
	u64 host_range_start, host_range_end, dram_range_start,
		dram_range_end;

	atomic64_set(&ctx->dram_phys_mem, 0);

	/*
	 * - If MMU is enabled, init the ranges as usual.
	 * - If MMU is disabled, in case of host mapping, the returned address
	 *   is the given one.
	 *   In case of DRAM mapping, the returned address is the physical
	 *   address of the memory related to the given handle.
	 */
	if (ctx->hdev->mmu_enable) {
		dram_range_start = prop->va_space_dram_start_address;
		dram_range_end = prop->va_space_dram_end_address;
		host_range_start = prop->va_space_host_start_address;
		host_range_end = prop->va_space_host_end_address;
	} else {
		dram_range_start = prop->dram_user_base_address;
		dram_range_end = prop->dram_end_address;
		host_range_start = prop->dram_user_base_address;
		host_range_end = prop->dram_end_address;
	}

	return hl_vm_ctx_init_with_ranges(ctx, host_range_start, host_range_end,
			dram_range_start, dram_range_end);
}