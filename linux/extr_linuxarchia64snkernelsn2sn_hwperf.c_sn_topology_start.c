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
struct seq_file {struct sn_hwperf_object_info* private; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ sn_hwperf_obj_cnt ; 

__attribute__((used)) static void *sn_topology_start(struct seq_file *s, loff_t * pos)
{
	struct sn_hwperf_object_info *objs = s->private;

	if (*pos < sn_hwperf_obj_cnt)
		return (void *)(objs + *pos);

	return NULL;
}