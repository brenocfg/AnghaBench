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
struct ksz_device {int on_ports; int live_ports; } ;
struct dsa_switch {struct ksz_device* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_is_user_port (struct dsa_switch*,int) ; 

void ksz_disable_port(struct dsa_switch *ds, int port)
{
	struct ksz_device *dev = ds->priv;

	if (!dsa_is_user_port(ds, port))
		return;

	dev->on_ports &= ~(1 << port);
	dev->live_ports &= ~(1 << port);

	/* port_stp_state_set() will be called after to disable the port so
	 * there is no need to do anything.
	 */
}