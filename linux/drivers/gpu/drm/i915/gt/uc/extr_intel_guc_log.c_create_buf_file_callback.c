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
typedef  int /*<<< orphan*/  umode_t ;
struct rchan_buf {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 struct dentry* debugfs_create_file (char const*,int /*<<< orphan*/ ,struct dentry*,struct rchan_buf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  relay_file_operations ; 

__attribute__((used)) static struct dentry *create_buf_file_callback(const char *filename,
					       struct dentry *parent,
					       umode_t mode,
					       struct rchan_buf *buf,
					       int *is_global)
{
	struct dentry *buf_file;

	/*
	 * This to enable the use of a single buffer for the relay channel and
	 * correspondingly have a single file exposed to User, through which
	 * it can collect the logs in order without any post-processing.
	 * Need to set 'is_global' even if parent is NULL for early logging.
	 */
	*is_global = 1;

	if (!parent)
		return NULL;

	buf_file = debugfs_create_file(filename, mode,
				       parent, buf, &relay_file_operations);
	if (IS_ERR(buf_file))
		return NULL;

	return buf_file;
}