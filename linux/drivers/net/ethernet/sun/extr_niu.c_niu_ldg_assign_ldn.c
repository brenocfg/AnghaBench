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
struct niu_parent {int* ldg_map; } ;
struct niu {int /*<<< orphan*/  port; int /*<<< orphan*/  device; TYPE_1__* parent; } ;
struct TYPE_2__ {scalar_t__ plat_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LDG_NUM (int) ; 
 int LDN_MAX ; 
 int NIU_LDG_MAX ; 
 int NIU_LDG_MIN ; 
 scalar_t__ PLAT_TYPE_NIU ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,unsigned long long) ; 
 int nr64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int niu_ldg_assign_ldn(struct niu *np, struct niu_parent *parent,
			      int ldg, int ldn)
{
	if (ldg < NIU_LDG_MIN || ldg > NIU_LDG_MAX)
		return -EINVAL;
	if (ldn < 0 || ldn > LDN_MAX)
		return -EINVAL;

	parent->ldg_map[ldn] = ldg;

	if (np->parent->plat_type == PLAT_TYPE_NIU) {
		/* On N2 NIU, the ldn-->ldg assignments are setup and fixed by
		 * the firmware, and we're not supposed to change them.
		 * Validate the mapping, because if it's wrong we probably
		 * won't get any interrupts and that's painful to debug.
		 */
		if (nr64(LDG_NUM(ldn)) != ldg) {
			dev_err(np->device, "Port %u, mis-matched LDG assignment for ldn %d, should be %d is %llu\n",
				np->port, ldn, ldg,
				(unsigned long long) nr64(LDG_NUM(ldn)));
			return -EINVAL;
		}
	} else
		nw64(LDG_NUM(ldn), ldg);

	return 0;
}