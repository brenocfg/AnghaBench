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
typedef  int /*<<< orphan*/  u32 ;
struct ingenic_ecc {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ BCH_BHCSR ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void jz4725b_bch_config_set(struct ingenic_ecc *bch, u32 cfg)
{
	writel(cfg, bch->base + BCH_BHCSR);
}