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
typedef  scalar_t__ u32 ;
struct rocker_wait {scalar_t__ nowait; } ;
struct rocker_desc_info {int dummy; } ;
struct rocker {int /*<<< orphan*/  cmd_ring; int /*<<< orphan*/  cmd_ring_lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct rocker_wait* rocker_desc_cookie_ptr_get (struct rocker_desc_info const*) ; 
 int /*<<< orphan*/  rocker_desc_gen_clear (struct rocker_desc_info const*) ; 
 struct rocker_desc_info* rocker_desc_tail_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rocker_dma_ring_credits_set (struct rocker*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  rocker_wait_wake_up (struct rocker_wait*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t rocker_cmd_irq_handler(int irq, void *dev_id)
{
	struct rocker *rocker = dev_id;
	const struct rocker_desc_info *desc_info;
	struct rocker_wait *wait;
	u32 credits = 0;

	spin_lock(&rocker->cmd_ring_lock);
	while ((desc_info = rocker_desc_tail_get(&rocker->cmd_ring))) {
		wait = rocker_desc_cookie_ptr_get(desc_info);
		if (wait->nowait) {
			rocker_desc_gen_clear(desc_info);
		} else {
			rocker_wait_wake_up(wait);
		}
		credits++;
	}
	spin_unlock(&rocker->cmd_ring_lock);
	rocker_dma_ring_credits_set(rocker, &rocker->cmd_ring, credits);

	return IRQ_HANDLED;
}