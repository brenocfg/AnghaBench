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
struct ocelot_port {struct ocelot* ocelot; } ;
struct ocelot {int /*<<< orphan*/  hwtstamp_config; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ocelot_hwstamp_get(struct ocelot_port *port, struct ifreq *ifr)
{
	struct ocelot *ocelot = port->ocelot;

	return copy_to_user(ifr->ifr_data, &ocelot->hwtstamp_config,
			    sizeof(ocelot->hwtstamp_config)) ? -EFAULT : 0;
}