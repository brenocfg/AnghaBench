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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {TYPE_1__* cmp_mask; } ;
struct arm_ccn {TYPE_2__ dt; } ;
struct TYPE_3__ {int /*<<< orphan*/  h; int /*<<< orphan*/  l; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ isdigit (char const) ; 
 int /*<<< orphan*/  isxdigit (char const) ; 
 int tolower (char const) ; 

__attribute__((used)) static u64 *arm_ccn_pmu_get_cmp_mask(struct arm_ccn *ccn, const char *name)
{
	unsigned long i;

	if (WARN_ON(!name || !name[0] || !isxdigit(name[0]) || !name[1]))
		return NULL;
	i = isdigit(name[0]) ? name[0] - '0' : 0xa + tolower(name[0]) - 'a';

	switch (name[1]) {
	case 'l':
		return &ccn->dt.cmp_mask[i].l;
	case 'h':
		return &ccn->dt.cmp_mask[i].h;
	default:
		return NULL;
	}
}