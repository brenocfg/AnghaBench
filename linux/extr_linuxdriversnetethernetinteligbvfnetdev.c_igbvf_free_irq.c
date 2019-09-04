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
struct net_device {int dummy; } ;
struct igbvf_adapter {TYPE_1__* msix_entries; struct net_device* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static void igbvf_free_irq(struct igbvf_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int vector;

	if (adapter->msix_entries) {
		for (vector = 0; vector < 3; vector++)
			free_irq(adapter->msix_entries[vector].vector, netdev);
	}
}