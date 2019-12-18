#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kiocb {TYPE_1__* ki_filp; struct ffs_io_data* private; } ;
struct ffs_io_data {scalar_t__ req; scalar_t__ ep; } ;
struct ffs_epfile {TYPE_2__* ffs; } ;
struct TYPE_4__ {int /*<<< orphan*/  eps_lock; } ;
struct TYPE_3__ {struct ffs_epfile* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENTER () ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int usb_ep_dequeue (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ffs_aio_cancel(struct kiocb *kiocb)
{
	struct ffs_io_data *io_data = kiocb->private;
	struct ffs_epfile *epfile = kiocb->ki_filp->private_data;
	int value;

	ENTER();

	spin_lock_irq(&epfile->ffs->eps_lock);

	if (likely(io_data && io_data->ep && io_data->req))
		value = usb_ep_dequeue(io_data->ep, io_data->req);
	else
		value = -EINVAL;

	spin_unlock_irq(&epfile->ffs->eps_lock);

	return value;
}