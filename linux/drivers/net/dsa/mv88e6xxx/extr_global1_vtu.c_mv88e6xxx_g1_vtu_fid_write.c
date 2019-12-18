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
typedef  int u16 ;
struct mv88e6xxx_vtu_entry {int fid; } ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6352_G1_VTU_FID ; 
 int MV88E6352_G1_VTU_FID_MASK ; 
 int mv88e6xxx_g1_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mv88e6xxx_g1_vtu_fid_write(struct mv88e6xxx_chip *chip,
				      struct mv88e6xxx_vtu_entry *entry)
{
	u16 val = entry->fid & MV88E6352_G1_VTU_FID_MASK;

	return mv88e6xxx_g1_write(chip, MV88E6352_G1_VTU_FID, val);
}