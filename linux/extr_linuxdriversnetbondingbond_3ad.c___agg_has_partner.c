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
struct aggregator {TYPE_1__ partner_system; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __agg_has_partner(struct aggregator *agg)
{
	return !is_zero_ether_addr(agg->partner_system.mac_addr_value);
}