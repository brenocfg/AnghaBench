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
struct c4iw_dev {int avail_ird; int /*<<< orphan*/  qps; } ;

/* Variables and functions */
 int /*<<< orphan*/  xa_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_ird(struct c4iw_dev *dev, int ird)
{
	xa_lock_irq(&dev->qps);
	dev->avail_ird += ird;
	xa_unlock_irq(&dev->qps);
}