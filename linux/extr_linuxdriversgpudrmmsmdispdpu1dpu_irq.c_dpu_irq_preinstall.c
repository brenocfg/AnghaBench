#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct msm_kms {int dummy; } ;
struct dpu_kms {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpu_core_irq_preinstall (struct dpu_kms*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct dpu_kms* to_dpu_kms (struct msm_kms*) ; 

void dpu_irq_preinstall(struct msm_kms *kms)
{
	struct dpu_kms *dpu_kms = to_dpu_kms(kms);

	if (!dpu_kms->dev || !dpu_kms->dev->dev) {
		pr_err("invalid device handles\n");
		return;
	}

	dpu_core_irq_preinstall(dpu_kms);
}