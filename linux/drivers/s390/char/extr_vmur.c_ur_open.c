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
typedef  int /*<<< orphan*/  u16 ;
struct urfile {int file_reclen; int /*<<< orphan*/  dev_reclen; } ;
struct urdev {scalar_t__ open_flag; scalar_t__ class; int /*<<< orphan*/  open_lock; int /*<<< orphan*/  reclen; int /*<<< orphan*/  wait; } ;
struct inode {int dummy; } ;
struct file {unsigned short f_flags; struct urfile* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_rdev; } ;

/* Variables and functions */
 scalar_t__ DEV_CLASS_UR_I ; 
 scalar_t__ DEV_CLASS_UR_O ; 
 int EACCES ; 
 int EBUSY ; 
 int ENOMEM ; 
 int ENXIO ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 unsigned short O_ACCMODE ; 
 int O_NONBLOCK ; 
 unsigned short O_RDONLY ; 
 unsigned short O_RDWR ; 
 unsigned short O_WRONLY ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 TYPE_1__* file_inode (struct file*) ; 
 int get_file_reclen (struct urdev*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct urdev* urdev_get_from_devno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  urdev_put (struct urdev*) ; 
 struct urfile* urfile_alloc (struct urdev*) ; 
 int /*<<< orphan*/  urfile_free (struct urfile*) ; 
 int verify_device (struct urdev*) ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ur_open(struct inode *inode, struct file *file)
{
	u16 devno;
	struct urdev *urd;
	struct urfile *urf;
	unsigned short accmode;
	int rc;

	accmode = file->f_flags & O_ACCMODE;

	if (accmode == O_RDWR)
		return -EACCES;
	/*
	 * We treat the minor number as the devno of the ur device
	 * to find in the driver tree.
	 */
	devno = MINOR(file_inode(file)->i_rdev);

	urd = urdev_get_from_devno(devno);
	if (!urd) {
		rc = -ENXIO;
		goto out;
	}

	spin_lock(&urd->open_lock);
	while (urd->open_flag) {
		spin_unlock(&urd->open_lock);
		if (file->f_flags & O_NONBLOCK) {
			rc = -EBUSY;
			goto fail_put;
		}
		if (wait_event_interruptible(urd->wait, urd->open_flag == 0)) {
			rc = -ERESTARTSYS;
			goto fail_put;
		}
		spin_lock(&urd->open_lock);
	}
	urd->open_flag++;
	spin_unlock(&urd->open_lock);

	TRACE("ur_open\n");

	if (((accmode == O_RDONLY) && (urd->class != DEV_CLASS_UR_I)) ||
	    ((accmode == O_WRONLY) && (urd->class != DEV_CLASS_UR_O))) {
		TRACE("ur_open: unsupported dev class (%d)\n", urd->class);
		rc = -EACCES;
		goto fail_unlock;
	}

	rc = verify_device(urd);
	if (rc)
		goto fail_unlock;

	urf = urfile_alloc(urd);
	if (!urf) {
		rc = -ENOMEM;
		goto fail_unlock;
	}

	urf->dev_reclen = urd->reclen;
	rc = get_file_reclen(urd);
	if (rc < 0)
		goto fail_urfile_free;
	urf->file_reclen = rc;
	file->private_data = urf;
	return 0;

fail_urfile_free:
	urfile_free(urf);
fail_unlock:
	spin_lock(&urd->open_lock);
	urd->open_flag--;
	spin_unlock(&urd->open_lock);
fail_put:
	urdev_put(urd);
out:
	return rc;
}