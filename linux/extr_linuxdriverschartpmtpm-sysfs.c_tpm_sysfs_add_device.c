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
struct tpm_chip {int flags; scalar_t__ groups_cnt; int /*<<< orphan*/ ** groups; } ;

/* Variables and functions */
 int TPM_CHIP_FLAG_TPM2 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  tpm_dev_group ; 

void tpm_sysfs_add_device(struct tpm_chip *chip)
{
	/* XXX: If you wish to remove this restriction, you must first update
	 * tpm_sysfs to explicitly lock chip->ops.
	 */
	if (chip->flags & TPM_CHIP_FLAG_TPM2)
		return;

	/* The sysfs routines rely on an implicit tpm_try_get_ops, device_del
	 * is called before ops is null'd and the sysfs core synchronizes this
	 * removal so that no callbacks are running or can run again
	 */
	WARN_ON(chip->groups_cnt != 0);
	chip->groups[chip->groups_cnt++] = &tpm_dev_group;
}