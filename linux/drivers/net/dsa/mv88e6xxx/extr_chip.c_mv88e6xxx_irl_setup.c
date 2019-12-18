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
struct mv88e6xxx_chip {TYPE_2__* info; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* irl_init_all ) (struct mv88e6xxx_chip*,int) ;} ;

/* Variables and functions */
 int mv88e6xxx_num_ports (struct mv88e6xxx_chip*) ; 
 int stub1 (struct mv88e6xxx_chip*,int) ; 

__attribute__((used)) static int mv88e6xxx_irl_setup(struct mv88e6xxx_chip *chip)
{
	int port;
	int err;

	if (!chip->info->ops->irl_init_all)
		return 0;

	for (port = 0; port < mv88e6xxx_num_ports(chip); port++) {
		/* Disable ingress rate limiting by resetting all per port
		 * ingress rate limit resources to their initial state.
		 */
		err = chip->info->ops->irl_init_all(chip, port);
		if (err)
			return err;
	}

	return 0;
}