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
struct clockdomain {int dummy; } ;
struct TYPE_2__ {struct clockdomain* ptr; int /*<<< orphan*/  name; } ;
struct clkdm_autodep {TYPE_1__ clkdm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct clockdomain* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct clockdomain* clkdm_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _autodep_lookup(struct clkdm_autodep *autodep)
{
	struct clockdomain *clkdm;

	if (!autodep)
		return;

	clkdm = clkdm_lookup(autodep->clkdm.name);
	if (!clkdm) {
		pr_err("clockdomain: autodeps: clockdomain %s does not exist\n",
			 autodep->clkdm.name);
		clkdm = ERR_PTR(-ENOENT);
	}
	autodep->clkdm.ptr = clkdm;
}