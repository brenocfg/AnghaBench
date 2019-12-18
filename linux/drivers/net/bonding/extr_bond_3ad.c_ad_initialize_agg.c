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
struct TYPE_2__ {int /*<<< orphan*/  mac_addr_value; } ;
struct aggregator {int /*<<< orphan*/ * slave; scalar_t__ aggregator_identifier; TYPE_1__ aggregator_mac_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad_clear_agg (struct aggregator*) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ad_initialize_agg(struct aggregator *aggregator)
{
	if (aggregator) {
		ad_clear_agg(aggregator);

		eth_zero_addr(aggregator->aggregator_mac_address.mac_addr_value);
		aggregator->aggregator_identifier = 0;
		aggregator->slave = NULL;
	}
}