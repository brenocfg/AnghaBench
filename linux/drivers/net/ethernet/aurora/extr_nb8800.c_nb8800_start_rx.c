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

/* Variables and functions */
 int /*<<< orphan*/  NB8800_RXC_CR ; 
 int /*<<< orphan*/  RCR_EN ; 
 int /*<<< orphan*/  nb8800_setl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 

__attribute__((used)) static void nb8800_start_rx(struct net_device *dev)
{
	nb8800_setl(netdev_priv(dev), NB8800_RXC_CR, RCR_EN);
}