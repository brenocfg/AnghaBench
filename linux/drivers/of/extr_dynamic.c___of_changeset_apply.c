#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct of_changeset {int dummy; } ;

/* Variables and functions */
 int __of_changeset_apply_entries (struct of_changeset*,int*) ; 
 int __of_changeset_apply_notify (struct of_changeset*) ; 

__attribute__((used)) static int __of_changeset_apply(struct of_changeset *ocs)
{
	int ret, ret_revert = 0;

	ret = __of_changeset_apply_entries(ocs, &ret_revert);
	if (!ret)
		ret = __of_changeset_apply_notify(ocs);

	return ret;
}