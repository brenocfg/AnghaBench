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
struct mv88e6xxx_chip {int /*<<< orphan*/  dev; TYPE_1__* info; } ;
struct TYPE_2__ {scalar_t__ global2_addr; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline int mv88e6xxx_g2_require(struct mv88e6xxx_chip *chip)
{
	if (chip->info->global2_addr) {
		dev_err(chip->dev, "this chip requires CONFIG_NET_DSA_MV88E6XXX_GLOBAL2 enabled\n");
		return -EOPNOTSUPP;
	}

	return 0;
}