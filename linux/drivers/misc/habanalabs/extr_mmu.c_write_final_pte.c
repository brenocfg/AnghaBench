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
struct hl_ctx {TYPE_2__* hdev; } ;
struct TYPE_4__ {TYPE_1__* asic_funcs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write_pte ) (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  get_phys_addr (struct hl_ctx*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void write_final_pte(struct hl_ctx *ctx, u64 shadow_pte_addr,
					u64 val)
{
	ctx->hdev->asic_funcs->write_pte(ctx->hdev,
					get_phys_addr(ctx, shadow_pte_addr),
					val);
	*(u64 *) (uintptr_t) shadow_pte_addr = val;
}