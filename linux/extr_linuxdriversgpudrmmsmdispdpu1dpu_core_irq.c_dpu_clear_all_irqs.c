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
struct dpu_kms {TYPE_2__* hw_intr; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* clear_all_irqs ) (TYPE_2__*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void dpu_clear_all_irqs(struct dpu_kms *dpu_kms)
{
	if (!dpu_kms || !dpu_kms->hw_intr ||
			!dpu_kms->hw_intr->ops.clear_all_irqs)
		return;

	dpu_kms->hw_intr->ops.clear_all_irqs(dpu_kms->hw_intr);
}