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
struct super_block {int s_time_gran; int /*<<< orphan*/  s_root; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; } ;
struct inode {int /*<<< orphan*/ * i_op; } ;
struct fs_context {int dummy; } ;
struct dev_data {int /*<<< orphan*/  dentry; struct super_block* sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ESRCH ; 
 int /*<<< orphan*/  GADGETFS_MAGIC ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int S_IFDIR ; 
 int S_IRUGO ; 
 int S_IXUGO ; 
 int /*<<< orphan*/  d_make_root (struct inode*) ; 
 struct dev_data* dev_new () ; 
 int /*<<< orphan*/  ep0_operations ; 
 int /*<<< orphan*/  gadget_fs_operations ; 
 int /*<<< orphan*/  gadgetfs_create_file (struct super_block*,int /*<<< orphan*/ ,struct dev_data*,int /*<<< orphan*/ *) ; 
 struct inode* gadgetfs_make_inode (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_dev (struct dev_data*) ; 
 int /*<<< orphan*/  simple_dir_inode_operations ; 
 int /*<<< orphan*/  simple_dir_operations ; 
 struct dev_data* the_device ; 
 int /*<<< orphan*/  usb_get_gadget_udc_name () ; 

__attribute__((used)) static int
gadgetfs_fill_super (struct super_block *sb, struct fs_context *fc)
{
	struct inode	*inode;
	struct dev_data	*dev;

	if (the_device)
		return -ESRCH;

	CHIP = usb_get_gadget_udc_name();
	if (!CHIP)
		return -ENODEV;

	/* superblock */
	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;
	sb->s_magic = GADGETFS_MAGIC;
	sb->s_op = &gadget_fs_operations;
	sb->s_time_gran = 1;

	/* root inode */
	inode = gadgetfs_make_inode (sb,
			NULL, &simple_dir_operations,
			S_IFDIR | S_IRUGO | S_IXUGO);
	if (!inode)
		goto Enomem;
	inode->i_op = &simple_dir_inode_operations;
	if (!(sb->s_root = d_make_root (inode)))
		goto Enomem;

	/* the ep0 file is named after the controller we expect;
	 * user mode code can use it for sanity checks, like we do.
	 */
	dev = dev_new ();
	if (!dev)
		goto Enomem;

	dev->sb = sb;
	dev->dentry = gadgetfs_create_file(sb, CHIP, dev, &ep0_operations);
	if (!dev->dentry) {
		put_dev(dev);
		goto Enomem;
	}

	/* other endpoint files are available after hardware setup,
	 * from binding to a controller.
	 */
	the_device = dev;
	return 0;

Enomem:
	return -ENOMEM;
}