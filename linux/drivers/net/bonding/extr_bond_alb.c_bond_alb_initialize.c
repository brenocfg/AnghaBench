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
struct TYPE_2__ {int rlb_enabled; } ;
struct bonding {TYPE_1__ alb_info; } ;

/* Variables and functions */
 int rlb_initialize (struct bonding*) ; 
 int /*<<< orphan*/  tlb_deinitialize (struct bonding*) ; 
 int tlb_initialize (struct bonding*) ; 

int bond_alb_initialize(struct bonding *bond, int rlb_enabled)
{
	int res;

	res = tlb_initialize(bond);
	if (res)
		return res;

	if (rlb_enabled) {
		bond->alb_info.rlb_enabled = 1;
		res = rlb_initialize(bond);
		if (res) {
			tlb_deinitialize(bond);
			return res;
		}
	} else {
		bond->alb_info.rlb_enabled = 0;
	}

	return 0;
}