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
struct ibmvmc_hmc {int /*<<< orphan*/  lock; } ;
struct ibmvmc_buffer {int free; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ibmvmc_free_hmc_buffer(struct ibmvmc_hmc *hmc,
				   struct ibmvmc_buffer *buffer)
{
	unsigned long flags;

	spin_lock_irqsave(&hmc->lock, flags);
	buffer->free = 1;
	spin_unlock_irqrestore(&hmc->lock, flags);
}