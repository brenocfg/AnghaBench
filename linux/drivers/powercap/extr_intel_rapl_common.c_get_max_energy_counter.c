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
typedef  int /*<<< orphan*/  u64 ;
struct rapl_domain {int dummy; } ;
struct powercap_zone {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENERGY_STATUS_MASK ; 
 int /*<<< orphan*/  ENERGY_UNIT ; 
 struct rapl_domain* power_zone_to_rapl_domain (struct powercap_zone*) ; 
 int /*<<< orphan*/  rapl_unit_xlate (struct rapl_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_max_energy_counter(struct powercap_zone *pcd_dev, u64 *energy)
{
	struct rapl_domain *rd = power_zone_to_rapl_domain(pcd_dev);

	*energy = rapl_unit_xlate(rd, ENERGY_UNIT, ENERGY_STATUS_MASK, 0);
	return 0;
}