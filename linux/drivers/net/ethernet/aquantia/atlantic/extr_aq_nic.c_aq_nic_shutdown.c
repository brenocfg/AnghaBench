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
struct aq_nic_s {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  aq_nic_deinit (struct aq_nic_s*) ; 
 int aq_nic_stop (struct aq_nic_s*) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

void aq_nic_shutdown(struct aq_nic_s *self)
{
	int err = 0;

	if (!self->ndev)
		return;

	rtnl_lock();

	netif_device_detach(self->ndev);

	if (netif_running(self->ndev)) {
		err = aq_nic_stop(self);
		if (err < 0)
			goto err_exit;
	}
	aq_nic_deinit(self);

err_exit:
	rtnl_unlock();
}