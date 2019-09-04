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

/* Variables and functions */
 scalar_t__ SN_HWPERF_FOREIGN (struct sn_hwperf_object_info*) ; 
 scalar_t__ SN_HWPERF_SAME_OBJTYPE (struct sn_hwperf_object_info*,struct sn_hwperf_object_info*) ; 

__attribute__((used)) static int sn_hwperf_generic_ordinal(struct sn_hwperf_object_info *obj,
				struct sn_hwperf_object_info *objs)
{
	int ordinal;
	struct sn_hwperf_object_info *p;

	for (ordinal=0, p=objs; p != obj; p++) {
		if (SN_HWPERF_FOREIGN(p))
			continue;
		if (SN_HWPERF_SAME_OBJTYPE(p, obj))
			ordinal++;
	}

	return ordinal;
}