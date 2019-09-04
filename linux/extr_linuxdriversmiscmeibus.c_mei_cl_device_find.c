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
typedef  int /*<<< orphan*/  uuid_le ;
typedef  scalar_t__ u8 ;
struct mei_cl_driver {struct mei_cl_device_id* id_table; } ;
struct mei_cl_device_id {scalar_t__ version; int /*<<< orphan*/  name; int /*<<< orphan*/  uuid; } ;
struct mei_cl_device {scalar_t__* name; int /*<<< orphan*/  me_cl; } ;

/* Variables and functions */
 scalar_t__ MEI_CL_VERSION_ANY ; 
 int /*<<< orphan*/  const NULL_UUID_LE ; 
 int /*<<< orphan*/ * mei_me_cl_uuid (int /*<<< orphan*/ ) ; 
 scalar_t__ mei_me_cl_ver (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uuid_le_cmp (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const
struct mei_cl_device_id *mei_cl_device_find(struct mei_cl_device *cldev,
					    struct mei_cl_driver *cldrv)
{
	const struct mei_cl_device_id *id;
	const uuid_le *uuid;
	u8 version;
	bool match;

	uuid = mei_me_cl_uuid(cldev->me_cl);
	version = mei_me_cl_ver(cldev->me_cl);

	id = cldrv->id_table;
	while (uuid_le_cmp(NULL_UUID_LE, id->uuid)) {
		if (!uuid_le_cmp(*uuid, id->uuid)) {
			match = true;

			if (cldev->name[0])
				if (strncmp(cldev->name, id->name,
					    sizeof(id->name)))
					match = false;

			if (id->version != MEI_CL_VERSION_ANY)
				if (id->version != version)
					match = false;
			if (match)
				return id;
		}

		id++;
	}

	return NULL;
}