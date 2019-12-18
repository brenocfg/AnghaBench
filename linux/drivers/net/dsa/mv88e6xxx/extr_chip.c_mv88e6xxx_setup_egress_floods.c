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
struct mv88e6xxx_chip {TYPE_2__* info; struct dsa_switch* ds; } ;
struct dsa_switch {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* port_set_egress_floods ) (struct mv88e6xxx_chip*,int,int,int) ;} ;

/* Variables and functions */
 scalar_t__ dsa_is_cpu_port (struct dsa_switch*,int) ; 
 scalar_t__ dsa_is_dsa_port (struct dsa_switch*,int) ; 
 int stub1 (struct mv88e6xxx_chip*,int,int,int) ; 

__attribute__((used)) static int mv88e6xxx_setup_egress_floods(struct mv88e6xxx_chip *chip, int port)
{
	struct dsa_switch *ds = chip->ds;
	bool flood;

	/* Upstream ports flood frames with unknown unicast or multicast DA */
	flood = dsa_is_cpu_port(ds, port) || dsa_is_dsa_port(ds, port);
	if (chip->info->ops->port_set_egress_floods)
		return chip->info->ops->port_set_egress_floods(chip, port,
							       flood, flood);

	return 0;
}