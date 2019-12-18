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
struct TYPE_2__ {int /*<<< orphan*/  rx_stopped; } ;
struct emac_instance {TYPE_1__ estats; } ;

/* Variables and functions */
 int /*<<< orphan*/  emac_rx_disable_async (struct emac_instance*) ; 

__attribute__((used)) static void emac_rxde(void *param)
{
	struct emac_instance *dev = param;

	++dev->estats.rx_stopped;
	emac_rx_disable_async(dev);
}