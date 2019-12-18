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
struct switchdev_obj_port_vlan {int /*<<< orphan*/  vid_end; int /*<<< orphan*/  vid_begin; } ;
struct mv88e6xxx_chip {TYPE_1__* info; } ;
struct dsa_switch {struct mv88e6xxx_chip* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_vid; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int mv88e6xxx_port_check_hw_vlan (struct dsa_switch*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static int
mv88e6xxx_port_vlan_prepare(struct dsa_switch *ds, int port,
			    const struct switchdev_obj_port_vlan *vlan)
{
	struct mv88e6xxx_chip *chip = ds->priv;
	int err;

	if (!chip->info->max_vid)
		return -EOPNOTSUPP;

	/* If the requested port doesn't belong to the same bridge as the VLAN
	 * members, do not support it (yet) and fallback to software VLAN.
	 */
	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_port_check_hw_vlan(ds, port, vlan->vid_begin,
					   vlan->vid_end);
	mv88e6xxx_reg_unlock(chip);

	/* We don't need any dynamic resource from the kernel (yet),
	 * so skip the prepare phase.
	 */
	return err;
}