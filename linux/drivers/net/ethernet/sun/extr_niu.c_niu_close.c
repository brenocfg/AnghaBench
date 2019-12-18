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
struct niu {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct niu* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  niu_free_channels (struct niu*) ; 
 int /*<<< orphan*/  niu_free_irq (struct niu*) ; 
 int /*<<< orphan*/  niu_full_shutdown (struct niu*,struct net_device*) ; 
 int /*<<< orphan*/  niu_handle_led (struct niu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int niu_close(struct net_device *dev)
{
	struct niu *np = netdev_priv(dev);

	niu_full_shutdown(np, dev);

	niu_free_irq(np);

	niu_free_channels(np);

	niu_handle_led(np, 0);

	return 0;
}