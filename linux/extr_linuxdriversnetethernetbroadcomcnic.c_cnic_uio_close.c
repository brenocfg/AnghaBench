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
struct uio_info {struct cnic_uio_dev* priv; } ;
struct inode {int dummy; } ;
struct cnic_uio_dev {int uio_dev; } ;

/* Variables and functions */

__attribute__((used)) static int cnic_uio_close(struct uio_info *uinfo, struct inode *inode)
{
	struct cnic_uio_dev *udev = uinfo->priv;

	udev->uio_dev = -1;
	return 0;
}