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
struct tape_device {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct tape_device* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*,...) ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct tape_device*) ; 
 int PTR_ERR (struct tape_device*) ; 
 int TAPE_MINORS_PER_DEV ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 scalar_t__ imajor (int /*<<< orphan*/ ) ; 
 int iminor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_open (struct inode*,struct file*) ; 
 struct tape_device* tape_find_device (int) ; 
 int tape_open (struct tape_device*) ; 
 int /*<<< orphan*/  tape_put_device (struct tape_device*) ; 
 scalar_t__ tapechar_major ; 

__attribute__((used)) static int
tapechar_open (struct inode *inode, struct file *filp)
{
	struct tape_device *device;
	int minor, rc;

	DBF_EVENT(6, "TCHAR:open: %i:%i\n",
		imajor(file_inode(filp)),
		iminor(file_inode(filp)));

	if (imajor(file_inode(filp)) != tapechar_major)
		return -ENODEV;

	minor = iminor(file_inode(filp));
	device = tape_find_device(minor / TAPE_MINORS_PER_DEV);
	if (IS_ERR(device)) {
		DBF_EVENT(3, "TCHAR:open: tape_find_device() failed\n");
		return PTR_ERR(device);
	}

	rc = tape_open(device);
	if (rc == 0) {
		filp->private_data = device;
		stream_open(inode, filp);
	} else
		tape_put_device(device);

	return rc;
}