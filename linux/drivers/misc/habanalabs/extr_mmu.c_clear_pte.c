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
typedef  int /*<<< orphan*/  u64 ;
struct hl_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_final_pte (struct hl_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void clear_pte(struct hl_ctx *ctx, u64 pte_addr)
{
	/* no need to transform the value to physical address */
	write_final_pte(ctx, pte_addr, 0);
}