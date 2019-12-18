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
struct nvmet_port {int enabled; int /*<<< orphan*/  referrals; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_config_sem ; 
 int /*<<< orphan*/  nvmet_port_disc_changed (struct nvmet_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void nvmet_referral_enable(struct nvmet_port *parent, struct nvmet_port *port)
{
	down_write(&nvmet_config_sem);
	if (list_empty(&port->entry)) {
		list_add_tail(&port->entry, &parent->referrals);
		port->enabled = true;
		nvmet_port_disc_changed(parent, NULL);
	}
	up_write(&nvmet_config_sem);
}