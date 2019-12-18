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
struct mei_fixup {int /*<<< orphan*/  (* hook ) (struct mei_cl_device*) ;int /*<<< orphan*/  uuid; } ;
struct mei_cl_device {int /*<<< orphan*/  me_cl; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct mei_fixup*) ; 
 int /*<<< orphan*/  const MEI_UUID_ANY ; 
 struct mei_fixup* mei_fixups ; 
 int /*<<< orphan*/ * mei_me_cl_uuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mei_cl_device*) ; 
 scalar_t__ uuid_le_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

void mei_cl_bus_dev_fixup(struct mei_cl_device *cldev)
{
	struct mei_fixup *f;
	const uuid_le *uuid = mei_me_cl_uuid(cldev->me_cl);
	size_t i;

	for (i = 0; i < ARRAY_SIZE(mei_fixups); i++) {

		f = &mei_fixups[i];
		if (uuid_le_cmp(f->uuid, MEI_UUID_ANY) == 0 ||
		    uuid_le_cmp(f->uuid, *uuid) == 0)
			f->hook(cldev);
	}
}