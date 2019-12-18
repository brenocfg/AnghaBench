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
 int __of_changeset_revert (struct of_changeset*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_mutex ; 

int of_changeset_revert(struct of_changeset *ocs)
{
	int ret;

	mutex_lock(&of_mutex);
	ret = __of_changeset_revert(ocs);
	mutex_unlock(&of_mutex);

	return ret;
}