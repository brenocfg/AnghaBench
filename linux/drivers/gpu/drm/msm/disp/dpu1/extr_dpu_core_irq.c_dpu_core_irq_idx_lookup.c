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
typedef  int /*<<< orphan*/  u32 ;
struct dpu_kms {TYPE_2__* hw_intr; } ;
typedef  enum dpu_intr_type { ____Placeholder_dpu_intr_type } dpu_intr_type ;
struct TYPE_3__ {int (* irq_idx_lookup ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (int,int /*<<< orphan*/ ) ; 

int dpu_core_irq_idx_lookup(struct dpu_kms *dpu_kms,
		enum dpu_intr_type intr_type, u32 instance_idx)
{
	if (!dpu_kms || !dpu_kms->hw_intr ||
			!dpu_kms->hw_intr->ops.irq_idx_lookup)
		return -EINVAL;

	return dpu_kms->hw_intr->ops.irq_idx_lookup(intr_type,
			instance_idx);
}