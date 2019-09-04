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
 void* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  diag204_info_type ; 
 int hypfs_create_phys_cpu_files (void*,void*) ; 
 void* hypfs_mkdir (void*,char*) ; 
 int /*<<< orphan*/  phys_cpu__size (int /*<<< orphan*/ ) ; 
 int phys_hdr__cpus (int /*<<< orphan*/ ,void*) ; 
 int phys_hdr__size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *hypfs_create_phys_files(struct dentry *parent_dir, void *phys_hdr)
{
	int i;
	void *cpu_info;
	struct dentry *cpus_dir;

	cpus_dir = hypfs_mkdir(parent_dir, "cpus");
	if (IS_ERR(cpus_dir))
		return cpus_dir;
	cpu_info = phys_hdr + phys_hdr__size(diag204_info_type);
	for (i = 0; i < phys_hdr__cpus(diag204_info_type, phys_hdr); i++) {
		int rc;
		rc = hypfs_create_phys_cpu_files(cpus_dir, cpu_info);
		if (rc)
			return ERR_PTR(rc);
		cpu_info += phys_cpu__size(diag204_info_type);
	}
	return cpu_info;
}