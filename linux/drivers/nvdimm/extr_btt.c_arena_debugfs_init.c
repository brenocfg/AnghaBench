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
struct arena_info {int /*<<< orphan*/ * log_index; int /*<<< orphan*/  flags; int /*<<< orphan*/  info2off; int /*<<< orphan*/  logoff; int /*<<< orphan*/  mapoff; int /*<<< orphan*/  dataoff; int /*<<< orphan*/  infooff; int /*<<< orphan*/  nextoff; int /*<<< orphan*/  version_minor; int /*<<< orphan*/  version_major; int /*<<< orphan*/  nfree; int /*<<< orphan*/  external_lbasize; int /*<<< orphan*/  external_nlba; int /*<<< orphan*/  internal_lbasize; int /*<<< orphan*/  internal_nlba; int /*<<< orphan*/  external_lba_start; int /*<<< orphan*/  size; struct dentry* debugfs_dir; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 int /*<<< orphan*/  S_IRUGO ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_u16 (char*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_x32 (char*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_x64 (char*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void arena_debugfs_init(struct arena_info *a, struct dentry *parent,
				int idx)
{
	char dirname[32];
	struct dentry *d;

	/* If for some reason, parent bttN was not created, exit */
	if (!parent)
		return;

	snprintf(dirname, 32, "arena%d", idx);
	d = debugfs_create_dir(dirname, parent);
	if (IS_ERR_OR_NULL(d))
		return;
	a->debugfs_dir = d;

	debugfs_create_x64("size", S_IRUGO, d, &a->size);
	debugfs_create_x64("external_lba_start", S_IRUGO, d,
				&a->external_lba_start);
	debugfs_create_x32("internal_nlba", S_IRUGO, d, &a->internal_nlba);
	debugfs_create_u32("internal_lbasize", S_IRUGO, d,
				&a->internal_lbasize);
	debugfs_create_x32("external_nlba", S_IRUGO, d, &a->external_nlba);
	debugfs_create_u32("external_lbasize", S_IRUGO, d,
				&a->external_lbasize);
	debugfs_create_u32("nfree", S_IRUGO, d, &a->nfree);
	debugfs_create_u16("version_major", S_IRUGO, d, &a->version_major);
	debugfs_create_u16("version_minor", S_IRUGO, d, &a->version_minor);
	debugfs_create_x64("nextoff", S_IRUGO, d, &a->nextoff);
	debugfs_create_x64("infooff", S_IRUGO, d, &a->infooff);
	debugfs_create_x64("dataoff", S_IRUGO, d, &a->dataoff);
	debugfs_create_x64("mapoff", S_IRUGO, d, &a->mapoff);
	debugfs_create_x64("logoff", S_IRUGO, d, &a->logoff);
	debugfs_create_x64("info2off", S_IRUGO, d, &a->info2off);
	debugfs_create_x32("flags", S_IRUGO, d, &a->flags);
	debugfs_create_u32("log_index_0", S_IRUGO, d, &a->log_index[0]);
	debugfs_create_u32("log_index_1", S_IRUGO, d, &a->log_index[1]);
}