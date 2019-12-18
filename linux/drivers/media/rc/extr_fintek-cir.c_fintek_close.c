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
struct rc_dev {struct fintek_dev* priv; } ;
struct fintek_dev {int /*<<< orphan*/  fintek_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  fintek_disable_cir (struct fintek_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fintek_close(struct rc_dev *dev)
{
	struct fintek_dev *fintek = dev->priv;
	unsigned long flags;

	spin_lock_irqsave(&fintek->fintek_lock, flags);
	fintek_disable_cir(fintek);
	spin_unlock_irqrestore(&fintek->fintek_lock, flags);
}