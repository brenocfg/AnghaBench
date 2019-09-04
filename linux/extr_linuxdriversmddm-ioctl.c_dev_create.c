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
struct mapped_device {int dummy; } ;
struct file {int dummy; } ;
struct dm_ioctl {int flags; scalar_t__* uuid; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DM_ANY_MINOR ; 
 int DM_INACTIVE_PRESENT_FLAG ; 
 int DM_PERSISTENT_DEV_FLAG ; 
 int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dev_status (struct mapped_device*,struct dm_ioctl*) ; 
 int check_name (int /*<<< orphan*/ ) ; 
 int dm_create (int,struct mapped_device**) ; 
 int /*<<< orphan*/  dm_destroy (struct mapped_device*) ; 
 int dm_hash_insert (int /*<<< orphan*/ ,scalar_t__*,struct mapped_device*) ; 
 int /*<<< orphan*/  dm_put (struct mapped_device*) ; 
 int /*<<< orphan*/  huge_decode_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dev_create(struct file *filp, struct dm_ioctl *param, size_t param_size)
{
	int r, m = DM_ANY_MINOR;
	struct mapped_device *md;

	r = check_name(param->name);
	if (r)
		return r;

	if (param->flags & DM_PERSISTENT_DEV_FLAG)
		m = MINOR(huge_decode_dev(param->dev));

	r = dm_create(m, &md);
	if (r)
		return r;

	r = dm_hash_insert(param->name, *param->uuid ? param->uuid : NULL, md);
	if (r) {
		dm_put(md);
		dm_destroy(md);
		return r;
	}

	param->flags &= ~DM_INACTIVE_PRESENT_FLAG;

	__dev_status(md, param);

	dm_put(md);

	return 0;
}