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
struct sclp_sd_data {int /*<<< orphan*/  dsize_bytes; } ;
struct sclp_sd_file {int /*<<< orphan*/  kobj; int /*<<< orphan*/  data_mutex; struct sclp_sd_data data; int /*<<< orphan*/  di; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 char* kobject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,char const*,...) ; 
 int /*<<< orphan*/  sclp_sd_data_reset (struct sclp_sd_data*) ; 
 int sclp_sd_store_data (struct sclp_sd_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sclp_sd_file_update(struct sclp_sd_file *sd_file)
{
	const char *name = kobject_name(&sd_file->kobj);
	struct sclp_sd_data data;
	int rc;

	rc = sclp_sd_store_data(&data, sd_file->di);
	if (rc) {
		if (rc == -ENOENT) {
			pr_info("No data is available for the %s data entity\n",
				 name);
		}
		return rc;
	}

	mutex_lock(&sd_file->data_mutex);
	sclp_sd_data_reset(&sd_file->data);
	sd_file->data = data;
	mutex_unlock(&sd_file->data_mutex);

	pr_info("A %zu-byte %s data entity was retrieved\n", data.dsize_bytes,
		name);
	kobject_uevent(&sd_file->kobj, KOBJ_CHANGE);

	return 0;
}