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
struct blk_mq_hw_ctx {int /*<<< orphan*/  cpuhp_dead; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_BLK_MQ_DEAD ; 
 int /*<<< orphan*/  cpuhp_state_remove_instance_nocalls (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blk_mq_remove_cpuhp(struct blk_mq_hw_ctx *hctx)
{
	cpuhp_state_remove_instance_nocalls(CPUHP_BLK_MQ_DEAD,
					    &hctx->cpuhp_dead);
}