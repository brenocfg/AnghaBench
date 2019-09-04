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
struct TYPE_2__ {scalar_t__ ptr; } ;
struct clkdm_autodep {TYPE_1__ clkdm; } ;

/* Variables and functions */
 int EACCES ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  _autodep_lookup (struct clkdm_autodep*) ; 
 struct clkdm_autodep* autodeps ; 
 int /*<<< orphan*/  clkdm_list ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

int clkdm_register_autodeps(struct clkdm_autodep *ia)
{
	struct clkdm_autodep *a = NULL;

	if (list_empty(&clkdm_list))
		return -EACCES;

	if (!ia)
		return -EINVAL;

	if (autodeps)
		return -EEXIST;

	autodeps = ia;
	for (a = autodeps; a->clkdm.ptr; a++)
		_autodep_lookup(a);

	return 0;
}