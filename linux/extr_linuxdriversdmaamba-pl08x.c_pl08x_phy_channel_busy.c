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
struct pl08x_phy_chan {scalar_t__ reg_config; int /*<<< orphan*/  id; scalar_t__ reg_busy; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 unsigned int PL080_CONFIG_ACTIVE ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static int pl08x_phy_channel_busy(struct pl08x_phy_chan *ch)
{
	unsigned int val;

	/* If we have a special busy register, take a shortcut */
	if (ch->reg_busy) {
		val = readl(ch->reg_busy);
		return !!(val & BIT(ch->id));
	}
	val = readl(ch->reg_config);
	return val & PL080_CONFIG_ACTIVE;
}