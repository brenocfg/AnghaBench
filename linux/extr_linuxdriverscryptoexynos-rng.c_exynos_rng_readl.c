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
typedef  scalar_t__ u32 ;
struct exynos_rng_dev {scalar_t__ mem; } ;

/* Variables and functions */
 scalar_t__ readl_relaxed (scalar_t__) ; 

__attribute__((used)) static u32 exynos_rng_readl(struct exynos_rng_dev *rng, u32 offset)
{
	return readl_relaxed(rng->mem + offset);
}