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
struct hash_cell {scalar_t__ new_map; scalar_t__ uuid; scalar_t__ name; } ;
struct dm_ioctl {char* uuid; char* name; int /*<<< orphan*/  flags; scalar_t__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_INACTIVE_PRESENT_FLAG ; 
 struct hash_cell* __get_dev_cell (scalar_t__) ; 
 struct hash_cell* __get_name_cell (char*) ; 
 struct hash_cell* __get_uuid_cell (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,scalar_t__,int) ; 

__attribute__((used)) static struct hash_cell *__find_device_hash_cell(struct dm_ioctl *param)
{
	struct hash_cell *hc = NULL;

	if (*param->uuid) {
		if (*param->name || param->dev)
			return NULL;

		hc = __get_uuid_cell(param->uuid);
		if (!hc)
			return NULL;
	} else if (*param->name) {
		if (param->dev)
			return NULL;

		hc = __get_name_cell(param->name);
		if (!hc)
			return NULL;
	} else if (param->dev) {
		hc = __get_dev_cell(param->dev);
		if (!hc)
			return NULL;
	} else
		return NULL;

	/*
	 * Sneakily write in both the name and the uuid
	 * while we have the cell.
	 */
	strlcpy(param->name, hc->name, sizeof(param->name));
	if (hc->uuid)
		strlcpy(param->uuid, hc->uuid, sizeof(param->uuid));
	else
		param->uuid[0] = '\0';

	if (hc->new_map)
		param->flags |= DM_INACTIVE_PRESENT_FLAG;
	else
		param->flags &= ~DM_INACTIVE_PRESENT_FLAG;

	return hc;
}