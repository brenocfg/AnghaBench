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
struct clockdomain {int /*<<< orphan*/  name; int /*<<< orphan*/  wkdep_srcs; } ;
struct clkdm_dep {int wkdep_usecount; } ;
struct TYPE_2__ {int (* clkdm_add_wkdep ) (struct clockdomain*,struct clockdomain*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct clkdm_dep*) ; 
 int PTR_ERR (struct clkdm_dep*) ; 
 struct clkdm_dep* _clkdm_deps_lookup (struct clockdomain*,int /*<<< orphan*/ ) ; 
 TYPE_1__* arch_clkdm ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct clockdomain*,struct clockdomain*) ; 

__attribute__((used)) static int _clkdm_add_wkdep(struct clockdomain *clkdm1,
			    struct clockdomain *clkdm2)
{
	struct clkdm_dep *cd;
	int ret = 0;

	if (!clkdm1 || !clkdm2)
		return -EINVAL;

	cd = _clkdm_deps_lookup(clkdm2, clkdm1->wkdep_srcs);
	if (IS_ERR(cd))
		ret = PTR_ERR(cd);

	if (!arch_clkdm || !arch_clkdm->clkdm_add_wkdep)
		ret = -EINVAL;

	if (ret) {
		pr_debug("clockdomain: hardware cannot set/clear wake up of %s when %s wakes up\n",
			 clkdm1->name, clkdm2->name);
		return ret;
	}

	cd->wkdep_usecount++;
	if (cd->wkdep_usecount == 1) {
		pr_debug("clockdomain: hardware will wake up %s when %s wakes up\n",
			 clkdm1->name, clkdm2->name);

		ret = arch_clkdm->clkdm_add_wkdep(clkdm1, clkdm2);
	}

	return ret;
}