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
struct net_device {int dummy; } ;
struct jme_adapter {int /*<<< orphan*/  flags; int /*<<< orphan*/  link_changing; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_FLAG_POLL ; 
 int /*<<< orphan*/  JME_FLAG_SHUTDOWN ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jme_dynamic_pcc (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_shutdown_nic (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_start_pcc_timer (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_stop_pcc_timer (struct jme_adapter*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
jme_pcc_tasklet(unsigned long arg)
{
	struct jme_adapter *jme = (struct jme_adapter *)arg;
	struct net_device *netdev = jme->dev;

	if (unlikely(test_bit(JME_FLAG_SHUTDOWN, &jme->flags))) {
		jme_shutdown_nic(jme);
		return;
	}

	if (unlikely(!netif_carrier_ok(netdev) ||
		(atomic_read(&jme->link_changing) != 1)
	)) {
		jme_stop_pcc_timer(jme);
		return;
	}

	if (!(test_bit(JME_FLAG_POLL, &jme->flags)))
		jme_dynamic_pcc(jme);

	jme_start_pcc_timer(jme);
}