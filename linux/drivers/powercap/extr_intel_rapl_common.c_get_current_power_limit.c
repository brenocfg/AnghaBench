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
#define  PL1_ENABLE 129 
#define  PL2_ENABLE 128 
 int POWER_LIMIT1 ; 
 int POWER_LIMIT2 ; 
 int contraint_to_pl (struct rapl_domain*,int) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 struct rapl_domain* power_zone_to_rapl_domain (struct powercap_zone*) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 scalar_t__ rapl_read_data_raw (struct rapl_domain*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_current_power_limit(struct powercap_zone *power_zone, int cid,
				   u64 *data)
{
	struct rapl_domain *rd;
	u64 val;
	int prim;
	int ret = 0;
	int id;

	get_online_cpus();
	rd = power_zone_to_rapl_domain(power_zone);
	id = contraint_to_pl(rd, cid);
	if (id < 0) {
		ret = id;
		goto get_exit;
	}

	switch (rd->rpl[id].prim_id) {
	case PL1_ENABLE:
		prim = POWER_LIMIT1;
		break;
	case PL2_ENABLE:
		prim = POWER_LIMIT2;
		break;
	default:
		put_online_cpus();
		return -EINVAL;
	}
	if (rapl_read_data_raw(rd, prim, true, &val))
		ret = -EIO;
	else
		*data = val;

get_exit:
	put_online_cpus();

	return ret;
}