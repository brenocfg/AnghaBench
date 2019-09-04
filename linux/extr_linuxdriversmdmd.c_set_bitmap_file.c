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
struct TYPE_6__ {struct file* file; scalar_t__ offset; } ;
struct mddev {int /*<<< orphan*/  lock; TYPE_3__ bitmap_info; struct bitmap* bitmap; TYPE_2__* pers; scalar_t__ sync_thread; scalar_t__ recovery; int /*<<< orphan*/  thread; } ;
struct inode {int /*<<< orphan*/  i_writecount; int /*<<< orphan*/  i_mode; } ;
struct file {int f_mode; TYPE_1__* f_mapping; } ;
struct bitmap {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  quiesce; } ;
struct TYPE_4__ {struct inode* host; } ;

/* Variables and functions */
 int EBADF ; 
 int EBUSY ; 
 int EEXIST ; 
 int ENOENT ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  IS_ERR (struct bitmap*) ; 
 int PTR_ERR (struct bitmap*) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct file* fget (int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 struct bitmap* md_bitmap_create (struct mddev*,int) ; 
 int /*<<< orphan*/  md_bitmap_destroy (struct mddev*) ; 
 int md_bitmap_load (struct mddev*) ; 
 int /*<<< orphan*/  mddev_resume (struct mddev*) ; 
 int /*<<< orphan*/  mddev_suspend (struct mddev*) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_bitmap_file(struct mddev *mddev, int fd)
{
	int err = 0;

	if (mddev->pers) {
		if (!mddev->pers->quiesce || !mddev->thread)
			return -EBUSY;
		if (mddev->recovery || mddev->sync_thread)
			return -EBUSY;
		/* we should be able to change the bitmap.. */
	}

	if (fd >= 0) {
		struct inode *inode;
		struct file *f;

		if (mddev->bitmap || mddev->bitmap_info.file)
			return -EEXIST; /* cannot add when bitmap is present */
		f = fget(fd);

		if (f == NULL) {
			pr_warn("%s: error: failed to get bitmap file\n",
				mdname(mddev));
			return -EBADF;
		}

		inode = f->f_mapping->host;
		if (!S_ISREG(inode->i_mode)) {
			pr_warn("%s: error: bitmap file must be a regular file\n",
				mdname(mddev));
			err = -EBADF;
		} else if (!(f->f_mode & FMODE_WRITE)) {
			pr_warn("%s: error: bitmap file must open for write\n",
				mdname(mddev));
			err = -EBADF;
		} else if (atomic_read(&inode->i_writecount) != 1) {
			pr_warn("%s: error: bitmap file is already in use\n",
				mdname(mddev));
			err = -EBUSY;
		}
		if (err) {
			fput(f);
			return err;
		}
		mddev->bitmap_info.file = f;
		mddev->bitmap_info.offset = 0; /* file overrides offset */
	} else if (mddev->bitmap == NULL)
		return -ENOENT; /* cannot remove what isn't there */
	err = 0;
	if (mddev->pers) {
		if (fd >= 0) {
			struct bitmap *bitmap;

			bitmap = md_bitmap_create(mddev, -1);
			mddev_suspend(mddev);
			if (!IS_ERR(bitmap)) {
				mddev->bitmap = bitmap;
				err = md_bitmap_load(mddev);
			} else
				err = PTR_ERR(bitmap);
			if (err) {
				md_bitmap_destroy(mddev);
				fd = -1;
			}
			mddev_resume(mddev);
		} else if (fd < 0) {
			mddev_suspend(mddev);
			md_bitmap_destroy(mddev);
			mddev_resume(mddev);
		}
	}
	if (fd < 0) {
		struct file *f = mddev->bitmap_info.file;
		if (f) {
			spin_lock(&mddev->lock);
			mddev->bitmap_info.file = NULL;
			spin_unlock(&mddev->lock);
			fput(f);
		}
	}

	return err;
}