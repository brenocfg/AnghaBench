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
typedef  scalar_t__ uint ;
struct dm_ioctl {char* name; char* uuid; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,...) ; 
 int /*<<< orphan*/  DM_BUFFER_FULL_FLAG ; 
 int /*<<< orphan*/  DM_DATA_OUT_FLAG ; 
 scalar_t__ DM_DEV_CREATE_CMD ; 
 scalar_t__ DM_LIST_DEVICES_CMD ; 
 scalar_t__ DM_LIST_VERSIONS_CMD ; 
 int DM_NAME_LEN ; 
 scalar_t__ DM_REMOVE_ALL_CMD ; 
 int /*<<< orphan*/  DM_SECURE_DATA_FLAG ; 
 int /*<<< orphan*/  DM_UEVENT_GENERATED_FLAG ; 
 int DM_UUID_LEN ; 
 int EINVAL ; 

__attribute__((used)) static int validate_params(uint cmd, struct dm_ioctl *param)
{
	/* Always clear this flag */
	param->flags &= ~DM_BUFFER_FULL_FLAG;
	param->flags &= ~DM_UEVENT_GENERATED_FLAG;
	param->flags &= ~DM_SECURE_DATA_FLAG;
	param->flags &= ~DM_DATA_OUT_FLAG;

	/* Ignores parameters */
	if (cmd == DM_REMOVE_ALL_CMD ||
	    cmd == DM_LIST_DEVICES_CMD ||
	    cmd == DM_LIST_VERSIONS_CMD)
		return 0;

	if (cmd == DM_DEV_CREATE_CMD) {
		if (!*param->name) {
			DMWARN("name not supplied when creating device");
			return -EINVAL;
		}
	} else if (*param->uuid && *param->name) {
		DMWARN("only supply one of name or uuid, cmd(%u)", cmd);
		return -EINVAL;
	}

	/* Ensure strings are terminated */
	param->name[DM_NAME_LEN - 1] = '\0';
	param->uuid[DM_UUID_LEN - 1] = '\0';

	return 0;
}