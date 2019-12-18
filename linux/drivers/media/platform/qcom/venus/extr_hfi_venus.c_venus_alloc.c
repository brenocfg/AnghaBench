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
typedef  int /*<<< orphan*/  u32 ;
struct venus_hfi_device {TYPE_1__* core; } ;
struct mem_desc {int /*<<< orphan*/  kva; int /*<<< orphan*/  attrs; int /*<<< orphan*/  da; int /*<<< orphan*/  size; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_ATTR_WRITE_COMBINE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SZ_4K ; 
 int /*<<< orphan*/  dma_alloc_attrs (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int venus_alloc(struct venus_hfi_device *hdev, struct mem_desc *desc,
		       u32 size)
{
	struct device *dev = hdev->core->dev;

	desc->attrs = DMA_ATTR_WRITE_COMBINE;
	desc->size = ALIGN(size, SZ_4K);

	desc->kva = dma_alloc_attrs(dev, desc->size, &desc->da, GFP_KERNEL,
				    desc->attrs);
	if (!desc->kva)
		return -ENOMEM;

	return 0;
}