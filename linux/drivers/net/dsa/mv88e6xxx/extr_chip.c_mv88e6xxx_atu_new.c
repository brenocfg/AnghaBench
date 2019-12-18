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
typedef  scalar_t__ u16 ;
struct mv88e6xxx_vtu_entry {scalar_t__ vid; int valid; scalar_t__ fid; } ;
struct mv88e6xxx_chip {TYPE_1__* info; } ;
struct TYPE_2__ {scalar_t__ max_vid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_BITMAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  MV88E6XXX_N_FID ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fid_bitmap ; 
 scalar_t__ find_next_zero_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mv88e6xxx_g1_atu_flush (struct mv88e6xxx_chip*,scalar_t__,int) ; 
 scalar_t__ mv88e6xxx_num_databases (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_num_ports (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_port_get_fid (struct mv88e6xxx_chip*,int,scalar_t__*) ; 
 int mv88e6xxx_vtu_getnext (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mv88e6xxx_atu_new(struct mv88e6xxx_chip *chip, u16 *fid)
{
	DECLARE_BITMAP(fid_bitmap, MV88E6XXX_N_FID);
	struct mv88e6xxx_vtu_entry vlan;
	int i, err;

	bitmap_zero(fid_bitmap, MV88E6XXX_N_FID);

	/* Set every FID bit used by the (un)bridged ports */
	for (i = 0; i < mv88e6xxx_num_ports(chip); ++i) {
		err = mv88e6xxx_port_get_fid(chip, i, fid);
		if (err)
			return err;

		set_bit(*fid, fid_bitmap);
	}

	/* Set every FID bit used by the VLAN entries */
	vlan.vid = chip->info->max_vid;
	vlan.valid = false;

	do {
		err = mv88e6xxx_vtu_getnext(chip, &vlan);
		if (err)
			return err;

		if (!vlan.valid)
			break;

		set_bit(vlan.fid, fid_bitmap);
	} while (vlan.vid < chip->info->max_vid);

	/* The reset value 0x000 is used to indicate that multiple address
	 * databases are not needed. Return the next positive available.
	 */
	*fid = find_next_zero_bit(fid_bitmap, MV88E6XXX_N_FID, 1);
	if (unlikely(*fid >= mv88e6xxx_num_databases(chip)))
		return -ENOSPC;

	/* Clear the database */
	return mv88e6xxx_g1_atu_flush(chip, *fid, true);
}