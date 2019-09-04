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
typedef  int /*<<< orphan*/  u32 ;
struct meson_gpio_irq_controller {int /*<<< orphan*/  channel_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int meson_gpio_irq_get_channel_idx (struct meson_gpio_irq_controller*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
meson_gpio_irq_release_channel(struct meson_gpio_irq_controller *ctl,
			       u32 *channel_hwirq)
{
	unsigned int idx;

	idx = meson_gpio_irq_get_channel_idx(ctl, channel_hwirq);
	clear_bit(idx, ctl->channel_map);
}