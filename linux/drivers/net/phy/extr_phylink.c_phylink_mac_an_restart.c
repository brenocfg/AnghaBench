#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  interface; scalar_t__ an_enabled; } ;
struct phylink {int /*<<< orphan*/  config; TYPE_2__* ops; TYPE_1__ link_config; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* mac_an_restart ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ phy_interface_mode_is_8023z (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phylink_mac_an_restart(struct phylink *pl)
{
	if (pl->link_config.an_enabled &&
	    phy_interface_mode_is_8023z(pl->link_config.interface))
		pl->ops->mac_an_restart(pl->config);
}