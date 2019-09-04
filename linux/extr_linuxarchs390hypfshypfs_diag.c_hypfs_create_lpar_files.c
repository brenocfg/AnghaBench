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
typedef  void dentry ;

/* Variables and functions */
 int DIAG204_LPAR_NAME_LEN ; 
 void* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  cpu_info__size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diag204_info_type ; 
 int hypfs_create_cpu_files (void*,void*) ; 
 void* hypfs_mkdir (void*,char*) ; 
 int /*<<< orphan*/  part_hdr__part_name (int /*<<< orphan*/ ,void*,char*) ; 
 int part_hdr__rcpus (int /*<<< orphan*/ ,void*) ; 
 int part_hdr__size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *hypfs_create_lpar_files(struct dentry *systems_dir, void *part_hdr)
{
	struct dentry *cpus_dir;
	struct dentry *lpar_dir;
	char lpar_name[DIAG204_LPAR_NAME_LEN + 1];
	void *cpu_info;
	int i;

	part_hdr__part_name(diag204_info_type, part_hdr, lpar_name);
	lpar_name[DIAG204_LPAR_NAME_LEN] = 0;
	lpar_dir = hypfs_mkdir(systems_dir, lpar_name);
	if (IS_ERR(lpar_dir))
		return lpar_dir;
	cpus_dir = hypfs_mkdir(lpar_dir, "cpus");
	if (IS_ERR(cpus_dir))
		return cpus_dir;
	cpu_info = part_hdr + part_hdr__size(diag204_info_type);
	for (i = 0; i < part_hdr__rcpus(diag204_info_type, part_hdr); i++) {
		int rc;
		rc = hypfs_create_cpu_files(cpus_dir, cpu_info);
		if (rc)
			return ERR_PTR(rc);
		cpu_info += cpu_info__size(diag204_info_type);
	}
	return cpu_info;
}