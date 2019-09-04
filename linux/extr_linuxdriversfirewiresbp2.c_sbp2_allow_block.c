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
struct sbp2_target {int /*<<< orphan*/  lock; int /*<<< orphan*/  dont_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void sbp2_allow_block(struct sbp2_target *tgt)
{
	spin_lock_irq(&tgt->lock);
	--tgt->dont_block;
	spin_unlock_irq(&tgt->lock);
}