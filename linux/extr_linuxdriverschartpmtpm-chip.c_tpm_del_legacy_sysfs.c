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
struct TYPE_5__ {TYPE_1__* parent; } ;
struct tpm_chip {int flags; TYPE_2__ dev; TYPE_3__** groups; } ;
struct attribute {char* name; } ;
struct TYPE_6__ {struct attribute** attrs; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int TPM_CHIP_FLAG_TPM2 ; 
 int TPM_CHIP_FLAG_VIRTUAL ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void tpm_del_legacy_sysfs(struct tpm_chip *chip)
{
	struct attribute **i;

	if (chip->flags & (TPM_CHIP_FLAG_TPM2 | TPM_CHIP_FLAG_VIRTUAL))
		return;

	sysfs_remove_link(&chip->dev.parent->kobj, "ppi");

	for (i = chip->groups[0]->attrs; *i != NULL; ++i)
		sysfs_remove_link(&chip->dev.parent->kobj, (*i)->name);
}