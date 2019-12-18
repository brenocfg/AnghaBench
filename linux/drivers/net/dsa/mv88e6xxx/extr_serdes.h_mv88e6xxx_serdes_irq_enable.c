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
struct TYPE_3__ {int (* serdes_irq_enable ) (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int mv88e6xxx_serdes_irq_enable(struct mv88e6xxx_chip *chip,
					      int port, u8 lane)
{
	if (!chip->info->ops->serdes_irq_enable)
		return -EOPNOTSUPP;

	return chip->info->ops->serdes_irq_enable(chip, port, lane, true);
}