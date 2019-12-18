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
struct file_operations {int dummy; } ;
struct file {int /*<<< orphan*/  f_mapping; } ;
struct cxl_context {int /*<<< orphan*/  pe; scalar_t__ mapping; } ;

/* Variables and functions */
 int EEXIST ; 
 struct file* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int O_CLOEXEC ; 
 int O_RDWR ; 
 int /*<<< orphan*/  PATCH_FOPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afu_fops ; 
 int /*<<< orphan*/  compat_ioctl ; 
 int /*<<< orphan*/  cxl_context_set_mapping (struct cxl_context*,int /*<<< orphan*/ ) ; 
 struct file* cxl_getfile (char*,struct file_operations*,struct cxl_context*,int) ; 
 int get_unused_fd_flags (int) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  mmap ; 
 int /*<<< orphan*/  open ; 
 int /*<<< orphan*/  poll ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 
 int /*<<< orphan*/  read ; 
 int /*<<< orphan*/  release ; 
 int /*<<< orphan*/  unlocked_ioctl ; 

struct file *cxl_get_fd(struct cxl_context *ctx, struct file_operations *fops,
			int *fd)
{
	struct file *file;
	int rc, flags, fdtmp;
	char *name = NULL;

	/* only allow one per context */
	if (ctx->mapping)
		return ERR_PTR(-EEXIST);

	flags = O_RDWR | O_CLOEXEC;

	/* This code is similar to anon_inode_getfd() */
	rc = get_unused_fd_flags(flags);
	if (rc < 0)
		return ERR_PTR(rc);
	fdtmp = rc;

	/*
	 * Patch the file ops.  Needs to be careful that this is rentrant safe.
	 */
	if (fops) {
		PATCH_FOPS(open);
		PATCH_FOPS(poll);
		PATCH_FOPS(read);
		PATCH_FOPS(release);
		PATCH_FOPS(unlocked_ioctl);
		PATCH_FOPS(compat_ioctl);
		PATCH_FOPS(mmap);
	} else /* use default ops */
		fops = (struct file_operations *)&afu_fops;

	name = kasprintf(GFP_KERNEL, "cxl:%d", ctx->pe);
	file = cxl_getfile(name, fops, ctx, flags);
	kfree(name);
	if (IS_ERR(file))
		goto err_fd;

	cxl_context_set_mapping(ctx, file->f_mapping);
	*fd = fdtmp;
	return file;

err_fd:
	put_unused_fd(fdtmp);
	return NULL;
}