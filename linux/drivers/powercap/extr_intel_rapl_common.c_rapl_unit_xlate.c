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
typedef  int u64 ;
struct rapl_package {int power_unit; int energy_unit; } ;
struct rapl_domain {int domain_energy_unit; struct rapl_package* rp; } ;
typedef  enum unit_type { ____Placeholder_unit_type } unit_type ;
struct TYPE_2__ {int (* compute_time_window ) (struct rapl_package*,int,int) ;} ;

/* Variables and functions */
#define  ARBITRARY_UNIT 131 
#define  ENERGY_UNIT 130 
 int ENERGY_UNIT_SCALE ; 
#define  POWER_UNIT 129 
#define  TIME_UNIT 128 
 int div64_u64 (int,int) ; 
 TYPE_1__* rapl_defaults ; 
 int stub1 (struct rapl_package*,int,int) ; 

__attribute__((used)) static u64 rapl_unit_xlate(struct rapl_domain *rd, enum unit_type type,
			   u64 value, int to_raw)
{
	u64 units = 1;
	struct rapl_package *rp = rd->rp;
	u64 scale = 1;

	switch (type) {
	case POWER_UNIT:
		units = rp->power_unit;
		break;
	case ENERGY_UNIT:
		scale = ENERGY_UNIT_SCALE;
		/* per domain unit takes precedence */
		if (rd->domain_energy_unit)
			units = rd->domain_energy_unit;
		else
			units = rp->energy_unit;
		break;
	case TIME_UNIT:
		return rapl_defaults->compute_time_window(rp, value, to_raw);
	case ARBITRARY_UNIT:
	default:
		return value;
	};

	if (to_raw)
		return div64_u64(value, units) * scale;

	value *= units;

	return div64_u64(value, scale);
}