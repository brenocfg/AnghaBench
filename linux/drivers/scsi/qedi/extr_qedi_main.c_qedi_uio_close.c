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
struct uio_info {struct qedi_uio_dev* priv; } ;
struct qedi_uio_dev {int uio_dev; struct qedi_ctx* qedi; } ;
struct qedi_ctx {int /*<<< orphan*/  flags; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIO_DEV_OPENED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qedi_ll2_free_skbs (struct qedi_ctx*) ; 

__attribute__((used)) static int qedi_uio_close(struct uio_info *uinfo, struct inode *inode)
{
	struct qedi_uio_dev *udev = uinfo->priv;
	struct qedi_ctx *qedi = udev->qedi;

	udev->uio_dev = -1;
	clear_bit(UIO_DEV_OPENED, &qedi->flags);
	qedi_ll2_free_skbs(qedi);
	return 0;
}