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
typedef  scalar_t__ u64 ;
struct hl_ctx {int asid; TYPE_2__* hdev; } ;
struct TYPE_3__ {int mmu_hop_table_size; } ;
struct TYPE_4__ {TYPE_1__ asic_prop; scalar_t__ mmu_shadow_hop0; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 get_hop0_addr(struct hl_ctx *ctx)
{
	return (u64) (uintptr_t) ctx->hdev->mmu_shadow_hop0 +
			(ctx->asid * ctx->hdev->asic_prop.mmu_hop_table_size);
}