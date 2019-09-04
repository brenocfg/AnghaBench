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
struct fimc_is {size_t config_index; int /*<<< orphan*/  slock; struct chain_config* config; } ;
struct chain_config {int /*<<< orphan*/ * p_region_index; } ;

/* Variables and functions */
 unsigned int hweight32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

unsigned int __get_pending_param_count(struct fimc_is *is)
{
	struct chain_config *config = &is->config[is->config_index];
	unsigned long flags;
	unsigned int count;

	spin_lock_irqsave(&is->slock, flags);
	count = hweight32(config->p_region_index[0]);
	count += hweight32(config->p_region_index[1]);
	spin_unlock_irqrestore(&is->slock, flags);

	return count;
}