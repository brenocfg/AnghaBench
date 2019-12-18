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
typedef  int u64 ;
struct hl_ctx {TYPE_2__* hdev; } ;
struct TYPE_4__ {TYPE_1__* asic_funcs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write_pte ) (TYPE_2__*,int,int) ;} ;

/* Variables and functions */
 int OFFSET_MASK ; 
 int PTE_PHYS_ADDR_MASK ; 
 int get_phys_addr (struct hl_ctx*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int) ; 

__attribute__((used)) static inline void write_pte(struct hl_ctx *ctx, u64 shadow_pte_addr, u64 val)
{
	/*
	 * The value to write is actually the address of the next shadow hop +
	 * flags at the 12 LSBs.
	 * Hence in order to get the value to write to the physical PTE, we
	 * clear the 12 LSBs and translate the shadow hop to its associated
	 * physical hop, and add back the original 12 LSBs.
	 */
	u64 phys_val = get_phys_addr(ctx, val & PTE_PHYS_ADDR_MASK) |
				(val & OFFSET_MASK);

	ctx->hdev->asic_funcs->write_pte(ctx->hdev,
					get_phys_addr(ctx, shadow_pte_addr),
					phys_val);

	*(u64 *) (uintptr_t) shadow_pte_addr = val;
}