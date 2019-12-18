#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct aac_dev {int /*<<< orphan*/  max_msix; TYPE_2__* init; int /*<<< orphan*/  sync_mode; scalar_t__ msi_enabled; } ;
struct TYPE_6__ {int /*<<< orphan*/  OMR; } ;
struct TYPE_4__ {int /*<<< orphan*/  no_of_msix_vectors; } ;
struct TYPE_5__ {TYPE_1__ r7; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_ENABLE_MSIX ; 
 unsigned long KERNEL_UP_AND_RUNNING ; 
 TYPE_3__ MUnit ; 
 scalar_t__ aac_acquire_irq (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_adapter_disable_int (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_adapter_enable_int (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_adapter_start (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_define_int_mode (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_fib_vector_assign (struct aac_dev*) ; 
 scalar_t__ aac_is_src (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_src_access_devreg (struct aac_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 unsigned long src_readl (struct aac_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aac_acquire_resources(struct aac_dev *dev)
{
	unsigned long status;
	/*
	 *	First clear out all interrupts.  Then enable the one's that we
	 *	can handle.
	 */
	while (!((status = src_readl(dev, MUnit.OMR)) & KERNEL_UP_AND_RUNNING)
		|| status == 0xffffffff)
			msleep(20);

	aac_adapter_disable_int(dev);
	aac_adapter_enable_int(dev);


	if (aac_is_src(dev))
		aac_define_int_mode(dev);

	if (dev->msi_enabled)
		aac_src_access_devreg(dev, AAC_ENABLE_MSIX);

	if (aac_acquire_irq(dev))
		goto error_iounmap;

	aac_adapter_enable_int(dev);

	/*max msix may change  after EEH
	 * Re-assign vectors to fibs
	 */
	aac_fib_vector_assign(dev);

	if (!dev->sync_mode) {
		/* After EEH recovery or suspend resume, max_msix count
		 * may change, therefore updating in init as well.
		 */
		dev->init->r7.no_of_msix_vectors = cpu_to_le32(dev->max_msix);
		aac_adapter_start(dev);
	}
	return 0;

error_iounmap:
	return -1;

}