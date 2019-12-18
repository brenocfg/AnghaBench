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
struct megasas_instance {scalar_t__ adapter_type; int /*<<< orphan*/  consumer_h; scalar_t__ consumer; TYPE_1__* pdev; int /*<<< orphan*/  producer_h; scalar_t__ producer; int /*<<< orphan*/  reply_map; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MFI_SERIES ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  megasas_free_fusion_context (struct megasas_instance*) ; 

__attribute__((used)) static inline void megasas_free_ctrl_mem(struct megasas_instance *instance)
{
	kfree(instance->reply_map);
	if (instance->adapter_type == MFI_SERIES) {
		if (instance->producer)
			dma_free_coherent(&instance->pdev->dev, sizeof(u32),
					    instance->producer,
					    instance->producer_h);
		if (instance->consumer)
			dma_free_coherent(&instance->pdev->dev, sizeof(u32),
					    instance->consumer,
					    instance->consumer_h);
	} else {
		megasas_free_fusion_context(instance);
	}
}