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
struct wm97xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB1300_AC97_PEN_INT ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void db1300_wm97xx_irqen(struct wm97xx *wm, int enable)
{
	if (enable)
		enable_irq(DB1300_AC97_PEN_INT);
	else
		disable_irq_nosync(DB1300_AC97_PEN_INT);
}