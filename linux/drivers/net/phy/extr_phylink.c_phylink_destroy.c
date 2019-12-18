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
struct phylink {int /*<<< orphan*/  resolve; scalar_t__ link_gpio; scalar_t__ sfp_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_put (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct phylink*) ; 
 int /*<<< orphan*/  sfp_unregister_upstream (scalar_t__) ; 

void phylink_destroy(struct phylink *pl)
{
	if (pl->sfp_bus)
		sfp_unregister_upstream(pl->sfp_bus);
	if (pl->link_gpio)
		gpiod_put(pl->link_gpio);

	cancel_work_sync(&pl->resolve);
	kfree(pl);
}