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
 int /*<<< orphan*/  HOP0_MASK ; 
 int /*<<< orphan*/  HOP0_SHIFT ; 
 int /*<<< orphan*/  get_hopN_pte_addr (struct hl_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 get_hop0_pte_addr(struct hl_ctx *ctx, u64 hop_addr, u64 vaddr)
{
	return get_hopN_pte_addr(ctx, hop_addr, vaddr, HOP0_MASK, HOP0_SHIFT);
}