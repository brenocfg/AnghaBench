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
typedef  int /*<<< orphan*/  u64 ;
struct rapl_domain {TYPE_1__* rpl; } ;
struct powercap_zone {int dummy; } ;
struct TYPE_2__ {int prim_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int MAX_POWER ; 
#define  PL1_ENABLE 129 
#define  PL2_ENABLE 128 
 int THERMAL_SPEC_POWER ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 struct rapl_domain* power_zone_to_rapl_domain (struct powercap_zone*) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 scalar_t__ rapl_read_data_raw (struct rapl_domain*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_max_power(struct powercap_zone *power_zone, int id, u64 *data)
{
	struct rapl_domain *rd;
	u64 val;
	int prim;
	int ret = 0;

	get_online_cpus();
	rd = power_zone_to_rapl_domain(power_zone);
	switch (rd->rpl[id].prim_id) {
	case PL1_ENABLE:
		prim = THERMAL_SPEC_POWER;
		break;
	case PL2_ENABLE:
		prim = MAX_POWER;
		break;
	default:
		put_online_cpus();
		return -EINVAL;
	}
	if (rapl_read_data_raw(rd, prim, true, &val))
		ret = -EIO;
	else
		*data = val;

	put_online_cpus();

	return ret;
}