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
struct megasas_instance {TYPE_1__* pdev; struct fusion_context* ctrl_context; } ;
struct fusion_context {TYPE_2__* ioc_init_cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  frame_phys_addr; scalar_t__ frame; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOC_INIT_FRAME_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

__attribute__((used)) static inline void megasas_free_ioc_init_cmd(struct megasas_instance *instance)
{
	struct fusion_context *fusion;

	fusion = instance->ctrl_context;

	if (fusion->ioc_init_cmd && fusion->ioc_init_cmd->frame)
		dma_free_coherent(&instance->pdev->dev,
				  IOC_INIT_FRAME_SIZE,
				  fusion->ioc_init_cmd->frame,
				  fusion->ioc_init_cmd->frame_phys_addr);

	kfree(fusion->ioc_init_cmd);
}