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
struct x_info_blk_hdr {int dummy; } ;
typedef  void dentry ;

/* Variables and functions */
 int DIAG204_LPAR_PHYS_FLG ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  diag204_info_type ; 
 void* diag204_store () ; 
 void* hypfs_create_lpar_files (void*,void*) ; 
 void* hypfs_create_phys_files (void*,void*) ; 
 void* hypfs_create_str (void*,char*,char*) ; 
 void* hypfs_mkdir (void*,char*) ; 
 int info_blk_hdr__flags (int /*<<< orphan*/ ,void*) ; 
 int info_blk_hdr__npar (int /*<<< orphan*/ ,void*) ; 
 int info_blk_hdr__size (int /*<<< orphan*/ ) ; 

int hypfs_diag_create_files(struct dentry *root)
{
	struct dentry *systems_dir, *hyp_dir;
	void *time_hdr, *part_hdr;
	int i, rc;
	void *buffer, *ptr;

	buffer = diag204_store();
	if (IS_ERR(buffer))
		return PTR_ERR(buffer);

	systems_dir = hypfs_mkdir(root, "systems");
	if (IS_ERR(systems_dir)) {
		rc = PTR_ERR(systems_dir);
		goto err_out;
	}
	time_hdr = (struct x_info_blk_hdr *)buffer;
	part_hdr = time_hdr + info_blk_hdr__size(diag204_info_type);
	for (i = 0; i < info_blk_hdr__npar(diag204_info_type, time_hdr); i++) {
		part_hdr = hypfs_create_lpar_files(systems_dir, part_hdr);
		if (IS_ERR(part_hdr)) {
			rc = PTR_ERR(part_hdr);
			goto err_out;
		}
	}
	if (info_blk_hdr__flags(diag204_info_type, time_hdr) &
	    DIAG204_LPAR_PHYS_FLG) {
		ptr = hypfs_create_phys_files(root, part_hdr);
		if (IS_ERR(ptr)) {
			rc = PTR_ERR(ptr);
			goto err_out;
		}
	}
	hyp_dir = hypfs_mkdir(root, "hyp");
	if (IS_ERR(hyp_dir)) {
		rc = PTR_ERR(hyp_dir);
		goto err_out;
	}
	ptr = hypfs_create_str(hyp_dir, "type", "LPAR Hypervisor");
	if (IS_ERR(ptr)) {
		rc = PTR_ERR(ptr);
		goto err_out;
	}
	rc = 0;

err_out:
	return rc;
}