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
struct mv88e6xxx_vtu_entry {scalar_t__ sid; int /*<<< orphan*/  valid; } ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int mv88e6xxx_g1_vtu_sid_read (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 
 int mv88e6xxx_g1_vtu_stu_getnext (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 

__attribute__((used)) static int mv88e6xxx_g1_vtu_stu_get(struct mv88e6xxx_chip *chip,
				    struct mv88e6xxx_vtu_entry *vtu)
{
	struct mv88e6xxx_vtu_entry stu;
	int err;

	err = mv88e6xxx_g1_vtu_sid_read(chip, vtu);
	if (err)
		return err;

	stu.sid = vtu->sid - 1;

	err = mv88e6xxx_g1_vtu_stu_getnext(chip, &stu);
	if (err)
		return err;

	if (stu.sid != vtu->sid || !stu.valid)
		return -EINVAL;

	return 0;
}