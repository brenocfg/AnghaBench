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
struct opa_vnic_adapter {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vema_enable_vport(int id, void *p, void *data)
{
	struct opa_vnic_adapter *adapter = p;

	netif_carrier_on(adapter->netdev);
	return 0;
}