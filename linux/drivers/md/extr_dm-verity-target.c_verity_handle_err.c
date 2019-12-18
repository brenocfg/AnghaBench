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
struct mapped_device {int dummy; } ;
struct dm_verity {int hash_failed; scalar_t__ corrupted_errs; scalar_t__ mode; TYPE_2__* data_dev; TYPE_1__* ti; } ;
typedef  enum verity_block_type { ____Placeholder_verity_block_type } verity_block_type ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMERR_LIMIT (char*,int /*<<< orphan*/ ,char const*,unsigned long long) ; 
#define  DM_VERITY_BLOCK_TYPE_DATA 129 
#define  DM_VERITY_BLOCK_TYPE_METADATA 128 
 int DM_VERITY_ENV_LENGTH ; 
 char* DM_VERITY_ENV_VAR_NAME ; 
 scalar_t__ DM_VERITY_MAX_CORRUPTED_ERRS ; 
 scalar_t__ DM_VERITY_MODE_LOGGING ; 
 scalar_t__ DM_VERITY_MODE_RESTART ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 TYPE_3__* disk_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_disk (struct mapped_device*) ; 
 struct mapped_device* dm_table_get_md (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_restart (char*) ; 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,unsigned long long) ; 

__attribute__((used)) static int verity_handle_err(struct dm_verity *v, enum verity_block_type type,
			     unsigned long long block)
{
	char verity_env[DM_VERITY_ENV_LENGTH];
	char *envp[] = { verity_env, NULL };
	const char *type_str = "";
	struct mapped_device *md = dm_table_get_md(v->ti->table);

	/* Corruption should be visible in device status in all modes */
	v->hash_failed = 1;

	if (v->corrupted_errs >= DM_VERITY_MAX_CORRUPTED_ERRS)
		goto out;

	v->corrupted_errs++;

	switch (type) {
	case DM_VERITY_BLOCK_TYPE_DATA:
		type_str = "data";
		break;
	case DM_VERITY_BLOCK_TYPE_METADATA:
		type_str = "metadata";
		break;
	default:
		BUG();
	}

	DMERR_LIMIT("%s: %s block %llu is corrupted", v->data_dev->name,
		    type_str, block);

	if (v->corrupted_errs == DM_VERITY_MAX_CORRUPTED_ERRS)
		DMERR("%s: reached maximum errors", v->data_dev->name);

	snprintf(verity_env, DM_VERITY_ENV_LENGTH, "%s=%d,%llu",
		DM_VERITY_ENV_VAR_NAME, type, block);

	kobject_uevent_env(&disk_to_dev(dm_disk(md))->kobj, KOBJ_CHANGE, envp);

out:
	if (v->mode == DM_VERITY_MODE_LOGGING)
		return 0;

	if (v->mode == DM_VERITY_MODE_RESTART)
		kernel_restart("dm-verity device corrupted");

	return 1;
}