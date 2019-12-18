#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct mv88e6xxx_chip {TYPE_3__* info; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {TYPE_1__* avb_ops; } ;
struct TYPE_4__ {int (* ptp_read ) (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mv88e6xxx_ptp_read(struct mv88e6xxx_chip *chip, int addr,
			      u16 *data)
{
	if (!chip->info->ops->avb_ops->ptp_read)
		return -EOPNOTSUPP;

	return chip->info->ops->avb_ops->ptp_read(chip, addr, data, 1);
}