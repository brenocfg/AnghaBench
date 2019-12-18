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
struct file {int dummy; } ;
struct drm_syncobj {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct file*) ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int PTR_ERR (struct file*) ; 
 struct file* anon_inode_getfile (char*,int /*<<< orphan*/ *,struct drm_syncobj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_syncobj_file_fops ; 
 int /*<<< orphan*/  drm_syncobj_get (struct drm_syncobj*) ; 
 int /*<<< orphan*/  fd_install (int,struct file*) ; 
 int get_unused_fd_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 

int drm_syncobj_get_fd(struct drm_syncobj *syncobj, int *p_fd)
{
	struct file *file;
	int fd;

	fd = get_unused_fd_flags(O_CLOEXEC);
	if (fd < 0)
		return fd;

	file = anon_inode_getfile("syncobj_file",
				  &drm_syncobj_file_fops,
				  syncobj, 0);
	if (IS_ERR(file)) {
		put_unused_fd(fd);
		return PTR_ERR(file);
	}

	drm_syncobj_get(syncobj);
	fd_install(fd, file);

	*p_fd = fd;
	return 0;
}