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
struct venus_hfi_device {TYPE_1__* core; } ;
struct mem_desc {int /*<<< orphan*/  attrs; int /*<<< orphan*/  da; int /*<<< orphan*/  kva; int /*<<< orphan*/  size; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_attrs (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void venus_free(struct venus_hfi_device *hdev, struct mem_desc *mem)
{
	struct device *dev = hdev->core->dev;

	dma_free_attrs(dev, mem->size, mem->kva, mem->da, mem->attrs);
}