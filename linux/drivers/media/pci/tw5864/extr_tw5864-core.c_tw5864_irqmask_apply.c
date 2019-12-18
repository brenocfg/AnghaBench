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
struct tw5864_dev {int irqmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  TW5864_INTR_ENABLE_H ; 
 int /*<<< orphan*/  TW5864_INTR_ENABLE_L ; 
 int /*<<< orphan*/  tw_writel (int /*<<< orphan*/ ,int) ; 

void tw5864_irqmask_apply(struct tw5864_dev *dev)
{
	tw_writel(TW5864_INTR_ENABLE_L, dev->irqmask & 0xffff);
	tw_writel(TW5864_INTR_ENABLE_H, (dev->irqmask >> 16));
}