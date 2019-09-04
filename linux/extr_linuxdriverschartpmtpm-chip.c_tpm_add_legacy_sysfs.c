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
struct TYPE_6__ {int /*<<< orphan*/  kobj; TYPE_2__* parent; } ;
struct tpm_chip {int flags; TYPE_3__ dev; TYPE_1__** groups; } ;
struct attribute {char* name; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {struct attribute** attrs; } ;

/* Variables and functions */
 int ENOENT ; 
 int TPM_CHIP_FLAG_TPM2 ; 
 int TPM_CHIP_FLAG_VIRTUAL ; 
 int __compat_only_sysfs_link_entry_to_kobj (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tpm_del_legacy_sysfs (struct tpm_chip*) ; 

__attribute__((used)) static int tpm_add_legacy_sysfs(struct tpm_chip *chip)
{
	struct attribute **i;
	int rc;

	if (chip->flags & (TPM_CHIP_FLAG_TPM2 | TPM_CHIP_FLAG_VIRTUAL))
		return 0;

	rc = __compat_only_sysfs_link_entry_to_kobj(
		    &chip->dev.parent->kobj, &chip->dev.kobj, "ppi");
	if (rc && rc != -ENOENT)
		return rc;

	/* All the names from tpm-sysfs */
	for (i = chip->groups[0]->attrs; *i != NULL; ++i) {
		rc = __compat_only_sysfs_link_entry_to_kobj(
		    &chip->dev.parent->kobj, &chip->dev.kobj, (*i)->name);
		if (rc) {
			tpm_del_legacy_sysfs(chip);
			return rc;
		}
	}

	return 0;
}