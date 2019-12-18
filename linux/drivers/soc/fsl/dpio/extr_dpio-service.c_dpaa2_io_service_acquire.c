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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct dpaa2_io {int /*<<< orphan*/  lock_mgmt_cmd; int /*<<< orphan*/  swp; } ;

/* Variables and functions */
 int ENODEV ; 
 int qbman_swp_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 struct dpaa2_io* service_select (struct dpaa2_io*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int dpaa2_io_service_acquire(struct dpaa2_io *d,
			     u16 bpid,
			     u64 *buffers,
			     unsigned int num_buffers)
{
	unsigned long irqflags;
	int err;

	d = service_select(d);
	if (!d)
		return -ENODEV;

	spin_lock_irqsave(&d->lock_mgmt_cmd, irqflags);
	err = qbman_swp_acquire(d->swp, bpid, buffers, num_buffers);
	spin_unlock_irqrestore(&d->lock_mgmt_cmd, irqflags);

	return err;
}