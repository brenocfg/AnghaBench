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
struct inode {int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; struct address_space* i_mapping; } ;
struct address_space {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ IS_SYNC (struct inode*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int filemap_fdatawait_range (struct address_space*,scalar_t__,scalar_t__) ; 
 int filemap_fdatawrite_range (struct address_space*,scalar_t__,scalar_t__) ; 
 int generic_cont_expand_simple (struct inode*,scalar_t__) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int sync_mapping_buffers (struct address_space*) ; 
 int write_inode_now (struct inode*,int) ; 

__attribute__((used)) static int exfat_cont_expand(struct inode *inode, loff_t size)
{
	struct address_space *mapping = inode->i_mapping;
	loff_t start = i_size_read(inode), count = size - i_size_read(inode);
	int err, err2;

	err = generic_cont_expand_simple(inode, size);
	if (err != 0)
		return err;

	inode->i_ctime = inode->i_mtime = current_time(inode);
	mark_inode_dirty(inode);

	if (IS_SYNC(inode)) {
		err = filemap_fdatawrite_range(mapping, start,
					       start + count - 1);
		err2 = sync_mapping_buffers(mapping);
		err = (err) ? (err) : (err2);
		err2 = write_inode_now(inode, 1);
		err = (err) ? (err) : (err2);
		if (!err)
			err =  filemap_fdatawait_range(mapping, start,
						       start + count - 1);
	}
	return err;
}