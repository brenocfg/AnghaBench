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
typedef  int /*<<< orphan*/  u8 ;
struct mv88e6xxx_chip {TYPE_2__* info; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* set_switch_mac ) (struct mv88e6xxx_chip*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  eth_random_addr (int /*<<< orphan*/ *) ; 
 int stub1 (struct mv88e6xxx_chip*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mv88e6xxx_mac_setup(struct mv88e6xxx_chip *chip)
{
	if (chip->info->ops->set_switch_mac) {
		u8 addr[ETH_ALEN];

		eth_random_addr(addr);

		return chip->info->ops->set_switch_mac(chip, addr);
	}

	return 0;
}