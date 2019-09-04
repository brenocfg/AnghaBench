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
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int REG_FILE_MODE ; 
 int S_IFREG ; 
 int TMP_SIZE ; 
 int /*<<< orphan*/  hypfs_add_dentry (struct dentry*) ; 
 struct dentry* hypfs_create_file (struct dentry*,char const*,char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long long) ; 

struct dentry *hypfs_create_u64(struct dentry *dir,
				const char *name, __u64 value)
{
	char *buffer;
	char tmp[TMP_SIZE];
	struct dentry *dentry;

	snprintf(tmp, TMP_SIZE, "%llu\n", (unsigned long long int)value);
	buffer = kstrdup(tmp, GFP_KERNEL);
	if (!buffer)
		return ERR_PTR(-ENOMEM);
	dentry =
	    hypfs_create_file(dir, name, buffer, S_IFREG | REG_FILE_MODE);
	if (IS_ERR(dentry)) {
		kfree(buffer);
		return ERR_PTR(-ENOMEM);
	}
	hypfs_add_dentry(dentry);
	return dentry;
}