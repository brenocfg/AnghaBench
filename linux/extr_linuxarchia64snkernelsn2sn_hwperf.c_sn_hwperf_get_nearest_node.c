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
struct sn_hwperf_object_info {int dummy; } ;
typedef  int /*<<< orphan*/  cnodeid_t ;

/* Variables and functions */
 int sn_hwperf_enum_objects (int*,struct sn_hwperf_object_info**) ; 
 int sn_hwperf_get_nearest_node_objdata (struct sn_hwperf_object_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (struct sn_hwperf_object_info*) ; 

int sn_hwperf_get_nearest_node(cnodeid_t node,
	cnodeid_t *near_mem_node, cnodeid_t *near_cpu_node)
{
	int e;
	int nobj;
	struct sn_hwperf_object_info *objbuf;

	if ((e = sn_hwperf_enum_objects(&nobj, &objbuf)) == 0) {
		e = sn_hwperf_get_nearest_node_objdata(objbuf, nobj,
			node, near_mem_node, near_cpu_node);
		vfree(objbuf);
	}

	return e;
}