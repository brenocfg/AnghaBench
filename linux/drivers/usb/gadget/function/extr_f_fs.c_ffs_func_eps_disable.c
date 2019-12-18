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
struct ffs_function {TYPE_1__* ffs; struct ffs_ep* eps; } ;
struct ffs_epfile {int /*<<< orphan*/ * ep; } ;
struct ffs_ep {int /*<<< orphan*/  ep; } ;
struct TYPE_2__ {unsigned int eps_count; int /*<<< orphan*/  eps_lock; struct ffs_epfile* epfiles; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ffs_epfile_read_buffer_free (struct ffs_epfile*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_ep_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ffs_func_eps_disable(struct ffs_function *func)
{
	struct ffs_ep *ep         = func->eps;
	struct ffs_epfile *epfile = func->ffs->epfiles;
	unsigned count            = func->ffs->eps_count;
	unsigned long flags;

	spin_lock_irqsave(&func->ffs->eps_lock, flags);
	while (count--) {
		/* pending requests get nuked */
		if (likely(ep->ep))
			usb_ep_disable(ep->ep);
		++ep;

		if (epfile) {
			epfile->ep = NULL;
			__ffs_epfile_read_buffer_free(epfile);
			++epfile;
		}
	}
	spin_unlock_irqrestore(&func->ffs->eps_lock, flags);
}