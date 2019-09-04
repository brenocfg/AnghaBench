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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int IR_FIRMODE ; 
 int IR_SIRMODE ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  lubbock_set_misc_wr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa2xx_transceiver_mode (struct device*,int) ; 

__attribute__((used)) static void lubbock_irda_transceiver_mode(struct device *dev, int mode)
{
	unsigned long flags;

	local_irq_save(flags);
	if (mode & IR_SIRMODE) {
		lubbock_set_misc_wr(BIT(4), 0);
	} else if (mode & IR_FIRMODE) {
		lubbock_set_misc_wr(BIT(4), BIT(4));
	}
	pxa2xx_transceiver_mode(dev, mode);
	local_irq_restore(flags);
}