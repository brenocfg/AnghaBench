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
struct isert_comp {int /*<<< orphan*/  active_qps; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_list_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isert_comp_put(struct isert_comp *comp)
{
	mutex_lock(&device_list_mutex);
	comp->active_qps--;
	mutex_unlock(&device_list_mutex);
}