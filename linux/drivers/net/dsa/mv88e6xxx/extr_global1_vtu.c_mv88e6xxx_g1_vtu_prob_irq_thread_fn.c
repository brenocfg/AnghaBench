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
typedef  int u16 ;
struct mv88e6xxx_vtu_entry {int /*<<< orphan*/  vid; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  dev; TYPE_1__* ports; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  vtu_miss_violation; int /*<<< orphan*/  vtu_member_violation; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MV88E6XXX_G1_VTU_OP ; 
 int /*<<< orphan*/  MV88E6XXX_G1_VTU_OP_GET_CLR_VIOLATION ; 
 int MV88E6XXX_G1_VTU_OP_MEMBER_VIOLATION ; 
 int MV88E6XXX_G1_VTU_OP_MISS_VIOLATION ; 
 int MV88E6XXX_G1_VTU_OP_SPID_MASK ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int mv88e6xxx_g1_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int*) ; 
 int mv88e6xxx_g1_vtu_op (struct mv88e6xxx_chip*,int /*<<< orphan*/ ) ; 
 int mv88e6xxx_g1_vtu_vid_read (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static irqreturn_t mv88e6xxx_g1_vtu_prob_irq_thread_fn(int irq, void *dev_id)
{
	struct mv88e6xxx_chip *chip = dev_id;
	struct mv88e6xxx_vtu_entry entry;
	int spid;
	int err;
	u16 val;

	mv88e6xxx_reg_lock(chip);

	err = mv88e6xxx_g1_vtu_op(chip, MV88E6XXX_G1_VTU_OP_GET_CLR_VIOLATION);
	if (err)
		goto out;

	err = mv88e6xxx_g1_read(chip, MV88E6XXX_G1_VTU_OP, &val);
	if (err)
		goto out;

	err = mv88e6xxx_g1_vtu_vid_read(chip, &entry);
	if (err)
		goto out;

	spid = val & MV88E6XXX_G1_VTU_OP_SPID_MASK;

	if (val & MV88E6XXX_G1_VTU_OP_MEMBER_VIOLATION) {
		dev_err_ratelimited(chip->dev, "VTU member violation for vid %d, source port %d\n",
				    entry.vid, spid);
		chip->ports[spid].vtu_member_violation++;
	}

	if (val & MV88E6XXX_G1_VTU_OP_MISS_VIOLATION) {
		dev_dbg_ratelimited(chip->dev, "VTU miss violation for vid %d, source port %d\n",
				    entry.vid, spid);
		chip->ports[spid].vtu_miss_violation++;
	}

	mv88e6xxx_reg_unlock(chip);

	return IRQ_HANDLED;

out:
	mv88e6xxx_reg_unlock(chip);

	dev_err(chip->dev, "VTU problem: error %d while handling interrupt\n",
		err);

	return IRQ_HANDLED;
}