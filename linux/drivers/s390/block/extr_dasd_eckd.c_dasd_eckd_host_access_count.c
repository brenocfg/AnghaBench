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
struct dasd_psf_query_host_access {scalar_t__ host_access_information; } ;
struct dasd_device {int /*<<< orphan*/  cdev; } ;
struct dasd_ckd_path_group_entry {int status_flags; } ;
struct dasd_ckd_host_information {int entry_count; int entry_size; scalar_t__ entry; } ;

/* Variables and functions */
 int DASD_ECKD_PG_GROUPED ; 
 int /*<<< orphan*/  DBF_EVENT_DEVID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int dasd_eckd_query_host_access (struct dasd_device*,struct dasd_psf_query_host_access*) ; 
 int /*<<< orphan*/  kfree (struct dasd_psf_query_host_access*) ; 
 struct dasd_psf_query_host_access* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dasd_eckd_host_access_count(struct dasd_device *device)
{
	struct dasd_psf_query_host_access *access;
	struct dasd_ckd_path_group_entry *entry;
	struct dasd_ckd_host_information *info;
	int count = 0;
	int rc, i;

	access = kzalloc(sizeof(*access), GFP_NOIO);
	if (!access) {
		DBF_EVENT_DEVID(DBF_WARNING, device->cdev, "%s",
				"Could not allocate access buffer");
		return -ENOMEM;
	}
	rc = dasd_eckd_query_host_access(device, access);
	if (rc) {
		kfree(access);
		return rc;
	}

	info = (struct dasd_ckd_host_information *)
		access->host_access_information;
	for (i = 0; i < info->entry_count; i++) {
		entry = (struct dasd_ckd_path_group_entry *)
			(info->entry + i * info->entry_size);
		if (entry->status_flags & DASD_ECKD_PG_GROUPED)
			count++;
	}

	kfree(access);
	return count;
}