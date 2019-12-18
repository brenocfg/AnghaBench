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
struct TYPE_2__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  cpu; } ;
struct lima_vm {TYPE_1__ pd; int /*<<< orphan*/  mm; int /*<<< orphan*/  refcount; int /*<<< orphan*/  lock; struct lima_device* dev; } ;
struct lima_device {int /*<<< orphan*/  dev; scalar_t__ va_start; scalar_t__ va_end; int /*<<< orphan*/  dlbu_dma; scalar_t__ dlbu_cpu; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 scalar_t__ LIMA_PAGE_SIZE ; 
 scalar_t__ LIMA_VA_RESERVE_DLBU ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  dma_alloc_wc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mm_init (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct lima_vm*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct lima_vm* kzalloc (int,int) ; 
 int lima_vm_map_page_table (struct lima_vm*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct lima_vm *lima_vm_create(struct lima_device *dev)
{
	struct lima_vm *vm;

	vm = kzalloc(sizeof(*vm), GFP_KERNEL);
	if (!vm)
		return NULL;

	vm->dev = dev;
	mutex_init(&vm->lock);
	kref_init(&vm->refcount);

	vm->pd.cpu = dma_alloc_wc(dev->dev, LIMA_PAGE_SIZE, &vm->pd.dma,
				  GFP_KERNEL | __GFP_ZERO);
	if (!vm->pd.cpu)
		goto err_out0;

	if (dev->dlbu_cpu) {
		int err = lima_vm_map_page_table(
			vm, &dev->dlbu_dma, LIMA_VA_RESERVE_DLBU,
			LIMA_VA_RESERVE_DLBU + LIMA_PAGE_SIZE - 1);
		if (err)
			goto err_out1;
	}

	drm_mm_init(&vm->mm, dev->va_start, dev->va_end - dev->va_start);

	return vm;

err_out1:
	dma_free_wc(dev->dev, LIMA_PAGE_SIZE, vm->pd.cpu, vm->pd.dma);
err_out0:
	kfree(vm);
	return NULL;
}