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
struct device {int dummy; } ;
struct arcnet_local {int /*<<< orphan*/  recon_led_trig; int /*<<< orphan*/  tx_led_trig; } ;

/* Variables and functions */
 int /*<<< orphan*/  led_trigger_unregister_simple (int /*<<< orphan*/ ) ; 
 struct arcnet_local* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_net_dev (struct device*) ; 

__attribute__((used)) static void arcnet_led_release(struct device *gendev, void *res)
{
	struct arcnet_local *lp = netdev_priv(to_net_dev(gendev));

	led_trigger_unregister_simple(lp->tx_led_trig);
	led_trigger_unregister_simple(lp->recon_led_trig);
}