#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_maxbytes; struct exfat_sb_info* s_fs_info; int /*<<< orphan*/  s_root; int /*<<< orphan*/ * s_export_op; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_flags; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct TYPE_5__ {int codepage; char* iocharset; } ;
struct TYPE_4__ {scalar_t__ vol_type; } ;
struct exfat_sb_info {TYPE_2__ options; void* nls_io; void* nls_disk; TYPE_1__ fs_info; int /*<<< orphan*/  s_lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_pos; } ;

/* Variables and functions */
 long EINVAL ; 
 long EIO ; 
 int ENOMEM ; 
 scalar_t__ EXFAT ; 
 TYPE_3__* EXFAT_I (struct inode*) ; 
 int /*<<< orphan*/  EXFAT_ROOT_INO ; 
 int /*<<< orphan*/  EXFAT_SUPER_MAGIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SB_NODIRATIME ; 
 int /*<<< orphan*/  SET_IVERSION (struct inode*,int) ; 
 int /*<<< orphan*/  d_make_root (struct inode*) ; 
 int /*<<< orphan*/  exfat_attach (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exfat_export_ops ; 
 int /*<<< orphan*/  exfat_free_super (struct exfat_sb_info*) ; 
 int /*<<< orphan*/  exfat_hash_init (struct super_block*) ; 
 long exfat_read_root (struct inode*) ; 
 int /*<<< orphan*/  exfat_sops ; 
 int ffsMountVol (struct super_block*) ; 
 int /*<<< orphan*/  ffsUmountVol (struct super_block*) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct exfat_sb_info* kvzalloc (int,int /*<<< orphan*/ ) ; 
 void* load_nls (char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct inode* new_inode (struct super_block*) ; 
 long parse_options (void*,int,int*,TYPE_2__*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  sb_min_blocksize (struct super_block*,int) ; 
 int /*<<< orphan*/  setup_dops (struct super_block*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int exfat_fill_super(struct super_block *sb, void *data, int silent)
{
	struct inode *root_inode = NULL;
	struct exfat_sb_info *sbi;
	int debug, ret;
	long error;
	char buf[50];

	/*
	 * GFP_KERNEL is ok here, because while we do hold the
	 * supeblock lock, memory pressure can't call back into
	 * the filesystem, since we're only just about to mount
	 * it and have no inodes etc active!
	 */
	sbi = kvzalloc(sizeof(*sbi), GFP_KERNEL);
	if (!sbi)
		return -ENOMEM;
	mutex_init(&sbi->s_lock);
	sb->s_fs_info = sbi;
	sb->s_flags |= SB_NODIRATIME;
	sb->s_magic = EXFAT_SUPER_MAGIC;
	sb->s_op = &exfat_sops;
	sb->s_export_op = &exfat_export_ops;

	error = parse_options(data, silent, &debug, &sbi->options);
	if (error)
		goto out_fail;

	setup_dops(sb);

	error = -EIO;
	sb_min_blocksize(sb, 512);
	sb->s_maxbytes = 0x7fffffffffffffffLL;    /* maximum file size */

	ret = ffsMountVol(sb);
	if (ret) {
		if (!silent)
			pr_err("[EXFAT] ffsMountVol failed\n");

		goto out_fail;
	}

	/* set up enough so that it can read an inode */
	exfat_hash_init(sb);

	/*
	 * The low byte of FAT's first entry must have same value with
	 * media-field.  But in real world, too many devices is
	 * writing wrong value.  So, removed that validity check.
	 *
	 * if (FAT_FIRST_ENT(sb, media) != first)
	 */

	/* codepage is not meaningful in exfat */
	if (sbi->fs_info.vol_type != EXFAT) {
		error = -EINVAL;
		sprintf(buf, "cp%d", sbi->options.codepage);
		sbi->nls_disk = load_nls(buf);
		if (!sbi->nls_disk) {
			pr_err("[EXFAT] Codepage %s not found\n", buf);
			goto out_fail2;
		}
	}

	sbi->nls_io = load_nls(sbi->options.iocharset);

	error = -ENOMEM;
	root_inode = new_inode(sb);
	if (!root_inode)
		goto out_fail2;
	root_inode->i_ino = EXFAT_ROOT_INO;
	SET_IVERSION(root_inode, 1);

	error = exfat_read_root(root_inode);
	if (error < 0)
		goto out_fail2;
	error = -ENOMEM;
	exfat_attach(root_inode, EXFAT_I(root_inode)->i_pos);
	insert_inode_hash(root_inode);
	sb->s_root = d_make_root(root_inode);
	if (!sb->s_root) {
		pr_err("[EXFAT] Getting the root inode failed\n");
		goto out_fail2;
	}

	return 0;

out_fail2:
	ffsUmountVol(sb);
out_fail:
	if (root_inode)
		iput(root_inode);
	sb->s_fs_info = NULL;
	exfat_free_super(sbi);
	return error;
}