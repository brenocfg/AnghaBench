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
struct dpu_kms {scalar_t__ mmio; int /*<<< orphan*/  core_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

__attribute__((used)) static inline void _dpu_kms_core_hw_rev_init(struct dpu_kms *dpu_kms)
{
	dpu_kms->core_rev = readl_relaxed(dpu_kms->mmio + 0x0);
}