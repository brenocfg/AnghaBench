#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct rapl_domain {TYPE_1__* rpl; int /*<<< orphan*/  state; int /*<<< orphan*/  name; TYPE_2__* rp; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int prim_id; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAIN_STATE_BIOS_LOCKED ; 
 int FW_LOCK ; 
 int NR_POWER_LIMITS ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rapl_read_data_raw (struct rapl_domain*,int,int,scalar_t__*) ; 

__attribute__((used)) static void rapl_detect_powerlimit(struct rapl_domain *rd)
{
	u64 val64;
	int i;

	/* check if the domain is locked by BIOS, ignore if MSR doesn't exist */
	if (!rapl_read_data_raw(rd, FW_LOCK, false, &val64)) {
		if (val64) {
			pr_info("RAPL %s domain %s locked by BIOS\n",
				rd->rp->name, rd->name);
			rd->state |= DOMAIN_STATE_BIOS_LOCKED;
		}
	}
	/* check if power limit MSR exists, otherwise domain is monitoring only */
	for (i = 0; i < NR_POWER_LIMITS; i++) {
		int prim = rd->rpl[i].prim_id;

		if (rapl_read_data_raw(rd, prim, false, &val64))
			rd->rpl[i].name = NULL;
	}
}