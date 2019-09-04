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
typedef  int u32 ;
struct ocelot_port {struct ocelot* ocelot; } ;
struct ocelot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANA_AUTOAGE ; 
 int /*<<< orphan*/  ANA_AUTOAGE_AGE_PERIOD (int) ; 
 unsigned long clock_t_to_jiffies (unsigned long) ; 
 int jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  ocelot_write (struct ocelot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocelot_port_attr_ageing_set(struct ocelot_port *ocelot_port,
					unsigned long ageing_clock_t)
{
	struct ocelot *ocelot = ocelot_port->ocelot;
	unsigned long ageing_jiffies = clock_t_to_jiffies(ageing_clock_t);
	u32 ageing_time = jiffies_to_msecs(ageing_jiffies) / 1000;

	ocelot_write(ocelot, ANA_AUTOAGE_AGE_PERIOD(ageing_time / 2),
		     ANA_AUTOAGE);
}