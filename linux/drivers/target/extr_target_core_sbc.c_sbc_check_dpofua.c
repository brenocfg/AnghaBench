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
struct se_device {int dummy; } ;
struct se_cmd {int /*<<< orphan*/  se_cmd_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SCF_FUA ; 
 int /*<<< orphan*/  pr_err (char*,unsigned char) ; 
 int /*<<< orphan*/  target_check_fua (struct se_device*) ; 

__attribute__((used)) static int
sbc_check_dpofua(struct se_device *dev, struct se_cmd *cmd, unsigned char *cdb)
{
	if (cdb[1] & 0x10) {
		/* see explanation in spc_emulate_modesense */
		if (!target_check_fua(dev)) {
			pr_err("Got CDB: 0x%02x with DPO bit set, but device"
			       " does not advertise support for DPO\n", cdb[0]);
			return -EINVAL;
		}
	}
	if (cdb[1] & 0x8) {
		if (!target_check_fua(dev)) {
			pr_err("Got CDB: 0x%02x with FUA bit set, but device"
			       " does not advertise support for FUA write\n",
			       cdb[0]);
			return -EINVAL;
		}
		cmd->se_cmd_flags |= SCF_FUA;
	}
	return 0;
}