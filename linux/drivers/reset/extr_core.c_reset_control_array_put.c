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
struct reset_control_array {int num_rstcs; int /*<<< orphan*/ * rstc; } ;

/* Variables and functions */
 int /*<<< orphan*/  __reset_control_put_internal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct reset_control_array*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_list_mutex ; 

__attribute__((used)) static void reset_control_array_put(struct reset_control_array *resets)
{
	int i;

	mutex_lock(&reset_list_mutex);
	for (i = 0; i < resets->num_rstcs; i++)
		__reset_control_put_internal(resets->rstc[i]);
	mutex_unlock(&reset_list_mutex);
	kfree(resets);
}