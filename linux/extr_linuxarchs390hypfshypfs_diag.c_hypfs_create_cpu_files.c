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
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ DIAG204_INFO_EXT ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int PTR_ERR_OR_ZERO (void*) ; 
 int TMP_SIZE ; 
 scalar_t__ cpu_info__acc_time (scalar_t__,void*) ; 
 int cpu_info__cpu_addr (scalar_t__,void*) ; 
 int /*<<< orphan*/  cpu_info__ctidx (scalar_t__,void*) ; 
 scalar_t__ cpu_info__lp_time (scalar_t__,void*) ; 
 scalar_t__ cpu_info__online_time (scalar_t__,void*) ; 
 scalar_t__ diag204_info_type ; 
 int /*<<< orphan*/  diag224_idx2name (int /*<<< orphan*/ ,char*) ; 
 void* hypfs_create_str (struct dentry*,char*,char*) ; 
 void* hypfs_create_u64 (struct dentry*,char*,scalar_t__) ; 
 struct dentry* hypfs_mkdir (struct dentry*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int hypfs_create_cpu_files(struct dentry *cpus_dir, void *cpu_info)
{
	struct dentry *cpu_dir;
	char buffer[TMP_SIZE];
	void *rc;

	snprintf(buffer, TMP_SIZE, "%d", cpu_info__cpu_addr(diag204_info_type,
							    cpu_info));
	cpu_dir = hypfs_mkdir(cpus_dir, buffer);
	rc = hypfs_create_u64(cpu_dir, "mgmtime",
			      cpu_info__acc_time(diag204_info_type, cpu_info) -
			      cpu_info__lp_time(diag204_info_type, cpu_info));
	if (IS_ERR(rc))
		return PTR_ERR(rc);
	rc = hypfs_create_u64(cpu_dir, "cputime",
			      cpu_info__lp_time(diag204_info_type, cpu_info));
	if (IS_ERR(rc))
		return PTR_ERR(rc);
	if (diag204_info_type == DIAG204_INFO_EXT) {
		rc = hypfs_create_u64(cpu_dir, "onlinetime",
				      cpu_info__online_time(diag204_info_type,
							    cpu_info));
		if (IS_ERR(rc))
			return PTR_ERR(rc);
	}
	diag224_idx2name(cpu_info__ctidx(diag204_info_type, cpu_info), buffer);
	rc = hypfs_create_str(cpu_dir, "type", buffer);
	return PTR_ERR_OR_ZERO(rc);
}