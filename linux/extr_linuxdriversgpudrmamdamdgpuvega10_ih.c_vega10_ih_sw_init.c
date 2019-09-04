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
struct TYPE_4__ {int use_doorbell; int doorbell_index; TYPE_3__* faults; } ;
struct TYPE_5__ {TYPE_1__ ih; } ;
struct amdgpu_device {TYPE_2__ irq; } ;
struct TYPE_6__ {scalar_t__ count; int /*<<< orphan*/  lock; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int AMDGPU_DOORBELL64_IH ; 
 int /*<<< orphan*/  AMDGPU_PAGEFAULT_HASH_BITS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_CHASH_TABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int amdgpu_ih_ring_init (struct amdgpu_device*,int,int) ; 
 int amdgpu_irq_init (struct amdgpu_device*) ; 
 TYPE_3__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vega10_ih_sw_init(void *handle)
{
	int r;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	r = amdgpu_ih_ring_init(adev, 256 * 1024, true);
	if (r)
		return r;

	adev->irq.ih.use_doorbell = true;
	adev->irq.ih.doorbell_index = AMDGPU_DOORBELL64_IH << 1;

	adev->irq.ih.faults = kmalloc(sizeof(*adev->irq.ih.faults), GFP_KERNEL);
	if (!adev->irq.ih.faults)
		return -ENOMEM;
	INIT_CHASH_TABLE(adev->irq.ih.faults->hash,
			 AMDGPU_PAGEFAULT_HASH_BITS, 8, 0);
	spin_lock_init(&adev->irq.ih.faults->lock);
	adev->irq.ih.faults->count = 0;

	r = amdgpu_irq_init(adev);

	return r;
}