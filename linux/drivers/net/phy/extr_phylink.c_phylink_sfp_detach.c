#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sfp_bus {int dummy; } ;
struct phylink {TYPE_1__* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * sfp_bus; } ;

/* Variables and functions */

__attribute__((used)) static void phylink_sfp_detach(void *upstream, struct sfp_bus *bus)
{
	struct phylink *pl = upstream;

	pl->netdev->sfp_bus = NULL;
}