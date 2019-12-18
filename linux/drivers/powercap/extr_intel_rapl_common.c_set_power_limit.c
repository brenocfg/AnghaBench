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
struct rapl_package {int dummy; } ;
struct rapl_domain {int state; TYPE_1__* rpl; int /*<<< orphan*/  name; struct rapl_package* rp; } ;
struct powercap_zone {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int prim_id; } ;

/* Variables and functions */
 int DOMAIN_STATE_BIOS_LOCKED ; 
 int EACCES ; 
 int EINVAL ; 
#define  PL1_ENABLE 129 
#define  PL2_ENABLE 128 
 int /*<<< orphan*/  POWER_LIMIT1 ; 
 int /*<<< orphan*/  POWER_LIMIT2 ; 
 int contraint_to_pl (struct rapl_domain*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  package_power_limit_irq_save (struct rapl_package*) ; 
 struct rapl_domain* power_zone_to_rapl_domain (struct powercap_zone*) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  rapl_write_data_raw (struct rapl_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_power_limit(struct powercap_zone *power_zone, int cid,
			   u64 power_limit)
{
	struct rapl_domain *rd;
	struct rapl_package *rp;
	int ret = 0;
	int id;

	get_online_cpus();
	rd = power_zone_to_rapl_domain(power_zone);
	id = contraint_to_pl(rd, cid);
	if (id < 0) {
		ret = id;
		goto set_exit;
	}

	rp = rd->rp;

	if (rd->state & DOMAIN_STATE_BIOS_LOCKED) {
		dev_warn(&power_zone->dev,
			 "%s locked by BIOS, monitoring only\n", rd->name);
		ret = -EACCES;
		goto set_exit;
	}

	switch (rd->rpl[id].prim_id) {
	case PL1_ENABLE:
		rapl_write_data_raw(rd, POWER_LIMIT1, power_limit);
		break;
	case PL2_ENABLE:
		rapl_write_data_raw(rd, POWER_LIMIT2, power_limit);
		break;
	default:
		ret = -EINVAL;
	}
	if (!ret)
		package_power_limit_irq_save(rp);
set_exit:
	put_online_cpus();
	return ret;
}