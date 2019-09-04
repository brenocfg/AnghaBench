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
struct qcom_iommu_ctx {unsigned int base; } ;

/* Variables and functions */
 int /*<<< orphan*/  writeq_relaxed (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void
iommu_writeq(struct qcom_iommu_ctx *ctx, unsigned reg, u64 val)
{
	writeq_relaxed(val, ctx->base + reg);
}