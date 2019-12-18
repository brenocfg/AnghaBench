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
struct megasas_instance {struct fusion_context* ctrl_context; } ;
struct fusion_context {int /*<<< orphan*/  reply_frames_desc_pool; int /*<<< orphan*/ * reply_frames_desc_phys; scalar_t__* reply_frames_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
megasas_free_reply_fusion(struct megasas_instance *instance) {

	struct fusion_context *fusion;

	fusion = instance->ctrl_context;

	if (fusion->reply_frames_desc[0])
		dma_pool_free(fusion->reply_frames_desc_pool,
			fusion->reply_frames_desc[0],
			fusion->reply_frames_desc_phys[0]);

	dma_pool_destroy(fusion->reply_frames_desc_pool);

}