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
typedef  int /*<<< orphan*/  uint8_t ;
struct kfd_process_device {int /*<<< orphan*/  scratch_base; int /*<<< orphan*/  scratch_limit; TYPE_2__* dev; scalar_t__ gpuvm_limit; int /*<<< orphan*/  gpuvm_base; int /*<<< orphan*/  lds_base; int /*<<< orphan*/  lds_limit; } ;
struct TYPE_3__ {scalar_t__ gpuvm_size; } ;
struct TYPE_4__ {TYPE_1__ shared_resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAKE_LDS_APP_BASE_V9 () ; 
 int /*<<< orphan*/  MAKE_LDS_APP_LIMIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKE_SCRATCH_APP_BASE_V9 () ; 
 int /*<<< orphan*/  MAKE_SCRATCH_APP_LIMIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVM_USER_BASE ; 

__attribute__((used)) static void kfd_init_apertures_v9(struct kfd_process_device *pdd, uint8_t id)
{
	pdd->lds_base = MAKE_LDS_APP_BASE_V9();
	pdd->lds_limit = MAKE_LDS_APP_LIMIT(pdd->lds_base);

	/* Raven needs SVM to support graphic handle, etc. Leave the small
	 * reserved space before SVM on Raven as well, even though we don't
	 * have to.
	 * Set gpuvm_base and gpuvm_limit to CANONICAL addresses so that they
	 * are used in Thunk to reserve SVM.
	 */
	pdd->gpuvm_base = SVM_USER_BASE;
	pdd->gpuvm_limit =
		pdd->dev->shared_resources.gpuvm_size - 1;

	pdd->scratch_base = MAKE_SCRATCH_APP_BASE_V9();
	pdd->scratch_limit = MAKE_SCRATCH_APP_LIMIT(pdd->scratch_base);
}