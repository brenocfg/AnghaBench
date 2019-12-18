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
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */

__attribute__((used)) static
void i2400m_tx_timeout(struct net_device *net_dev)
{
	/*
	 * We might want to kick the device
	 *
	 * There is not much we can do though, as the device requires
	 * that we send the data aggregated. By the time we receive
	 * this, there might be data pending to be sent or not...
	 */
	net_dev->stats.tx_errors++;
}