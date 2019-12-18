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
struct isert_device {int comps_used; struct isert_comp* comps; } ;
struct isert_conn {struct isert_device* device; } ;
struct isert_comp {scalar_t__ active_qps; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_list_mutex ; 
 int /*<<< orphan*/  isert_info (char*,struct isert_conn*,struct isert_comp*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct isert_comp *
isert_comp_get(struct isert_conn *isert_conn)
{
	struct isert_device *device = isert_conn->device;
	struct isert_comp *comp;
	int i, min = 0;

	mutex_lock(&device_list_mutex);
	for (i = 0; i < device->comps_used; i++)
		if (device->comps[i].active_qps <
		    device->comps[min].active_qps)
			min = i;
	comp = &device->comps[min];
	comp->active_qps++;
	mutex_unlock(&device_list_mutex);

	isert_info("conn %p, using comp %p min_index: %d\n",
		   isert_conn, comp, min);

	return comp;
}