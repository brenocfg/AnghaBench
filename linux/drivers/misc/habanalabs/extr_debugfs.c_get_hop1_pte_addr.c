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
struct TYPE_3__ {int mmu_pte_size; } ;
struct TYPE_4__ {TYPE_1__ asic_prop; } ;

/* Variables and functions */
 int HOP1_MASK ; 
 int HOP1_SHIFT ; 

__attribute__((used)) static inline u64 get_hop1_pte_addr(struct hl_ctx *ctx, u64 hop_addr,
		u64 virt_addr)
{
	return hop_addr + ctx->hdev->asic_prop.mmu_pte_size *
			((virt_addr & HOP1_MASK) >> HOP1_SHIFT);
}