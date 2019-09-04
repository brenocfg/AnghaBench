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
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int PTR_ERR_OR_ZERO (void*) ; 
 int TMP_SIZE ; 
 int /*<<< orphan*/  diag204_info_type ; 
 int /*<<< orphan*/  diag224_idx2name (int /*<<< orphan*/ ,char*) ; 
 void* hypfs_create_str (void*,char*,char*) ; 
 void* hypfs_create_u64 (void*,char*,int /*<<< orphan*/ ) ; 
 void* hypfs_mkdir (void*,char*) ; 
 int phys_cpu__cpu_addr (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  phys_cpu__ctidx (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  phys_cpu__mgm_time (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int hypfs_create_phys_cpu_files(struct dentry *cpus_dir, void *cpu_info)
{
	struct dentry *cpu_dir;
	char buffer[TMP_SIZE];
	void *rc;

	snprintf(buffer, TMP_SIZE, "%i", phys_cpu__cpu_addr(diag204_info_type,
							    cpu_info));
	cpu_dir = hypfs_mkdir(cpus_dir, buffer);
	if (IS_ERR(cpu_dir))
		return PTR_ERR(cpu_dir);
	rc = hypfs_create_u64(cpu_dir, "mgmtime",
			      phys_cpu__mgm_time(diag204_info_type, cpu_info));
	if (IS_ERR(rc))
		return PTR_ERR(rc);
	diag224_idx2name(phys_cpu__ctidx(diag204_info_type, cpu_info), buffer);
	rc = hypfs_create_str(cpu_dir, "type", buffer);
	return PTR_ERR_OR_ZERO(rc);
}