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
struct sn_hwperf_object_info {int id; } ;

/* Variables and functions */

__attribute__((used)) static struct sn_hwperf_object_info *
sn_hwperf_findobj_id(struct sn_hwperf_object_info *objbuf,
	int nobj, int id)
{
	int i;
	struct sn_hwperf_object_info *p = objbuf;

	for (i=0; i < nobj; i++, p++) {
		if (p->id == id)
			return p;
	}

	return NULL;

}