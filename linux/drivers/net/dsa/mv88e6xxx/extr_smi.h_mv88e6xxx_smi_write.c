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
typedef  int /*<<< orphan*/  u16 ;
struct mv88e6xxx_chip {TYPE_1__* smi_ops; } ;
struct TYPE_2__ {int (* write ) (struct mv88e6xxx_chip*,int,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct mv88e6xxx_chip*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int mv88e6xxx_smi_write(struct mv88e6xxx_chip *chip,
				      int dev, int reg, u16 data)
{
	if (chip->smi_ops && chip->smi_ops->write)
		return chip->smi_ops->write(chip, dev, reg, data);

	return -EOPNOTSUPP;
}