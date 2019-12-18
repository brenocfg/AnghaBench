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
struct msm_kms {int dummy; } ;
struct dpu_kms {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  _dpu_kms_hw_destroy (struct dpu_kms*) ; 
 struct dpu_kms* to_dpu_kms (struct msm_kms*) ; 

__attribute__((used)) static void dpu_kms_destroy(struct msm_kms *kms)
{
	struct dpu_kms *dpu_kms;

	if (!kms) {
		DPU_ERROR("invalid kms\n");
		return;
	}

	dpu_kms = to_dpu_kms(kms);

	_dpu_kms_hw_destroy(dpu_kms);
}