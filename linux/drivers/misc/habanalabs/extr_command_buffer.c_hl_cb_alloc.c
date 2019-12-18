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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hl_device {int /*<<< orphan*/  dev; TYPE_1__* asic_funcs; } ;
struct hl_cb {int /*<<< orphan*/  size; scalar_t__ kernel_address; int /*<<< orphan*/  bus_address; } ;
struct TYPE_2__ {void* (* asic_dma_alloc_coherent ) (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int GFP_ATOMIC ; 
 int GFP_KERNEL ; 
 int GFP_USER ; 
 int HL_KERNEL_ASID_ID ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hl_cb*) ; 
 struct hl_cb* kzalloc (int,int) ; 
 void* stub1 (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 void* stub2 (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct hl_cb *hl_cb_alloc(struct hl_device *hdev, u32 cb_size,
					int ctx_id)
{
	struct hl_cb *cb;
	void *p;

	/*
	 * We use of GFP_ATOMIC here because this function can be called from
	 * the latency-sensitive code path for command submission. Due to H/W
	 * limitations in some of the ASICs, the kernel must copy the user CB
	 * that is designated for an external queue and actually enqueue
	 * the kernel's copy. Hence, we must never sleep in this code section
	 * and must use GFP_ATOMIC for all memory allocations.
	 */
	if (ctx_id == HL_KERNEL_ASID_ID)
		cb = kzalloc(sizeof(*cb), GFP_ATOMIC);
	else
		cb = kzalloc(sizeof(*cb), GFP_KERNEL);

	if (!cb)
		return NULL;

	if (ctx_id == HL_KERNEL_ASID_ID)
		p = hdev->asic_funcs->asic_dma_alloc_coherent(hdev, cb_size,
						&cb->bus_address, GFP_ATOMIC);
	else
		p = hdev->asic_funcs->asic_dma_alloc_coherent(hdev, cb_size,
						&cb->bus_address,
						GFP_USER | __GFP_ZERO);
	if (!p) {
		dev_err(hdev->dev,
			"failed to allocate %d of dma memory for CB\n",
			cb_size);
		kfree(cb);
		return NULL;
	}

	cb->kernel_address = (u64) (uintptr_t) p;
	cb->size = cb_size;

	return cb;
}