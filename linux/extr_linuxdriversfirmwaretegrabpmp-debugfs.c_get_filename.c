#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tegra_bpmp {int /*<<< orphan*/  debugfs_mirror; } ;
struct TYPE_2__ {int /*<<< orphan*/  dentry; } ;
struct file {TYPE_1__ f_path; } ;
typedef  int /*<<< orphan*/  root_path_buf ;

/* Variables and functions */
 scalar_t__ IS_ERR (char const*) ; 
 char* dentry_path (int /*<<< orphan*/ ,char*,int) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static const char *get_filename(struct tegra_bpmp *bpmp,
				const struct file *file, char *buf, int size)
{
	char root_path_buf[512];
	const char *root_path;
	const char *filename;
	size_t root_len;

	root_path = dentry_path(bpmp->debugfs_mirror, root_path_buf,
				sizeof(root_path_buf));
	if (IS_ERR(root_path))
		return NULL;

	root_len = strlen(root_path);

	filename = dentry_path(file->f_path.dentry, buf, size);
	if (IS_ERR(filename))
		return NULL;

	if (strlen(filename) < root_len ||
			strncmp(filename, root_path, root_len))
		return NULL;

	filename += root_len;

	return filename;
}