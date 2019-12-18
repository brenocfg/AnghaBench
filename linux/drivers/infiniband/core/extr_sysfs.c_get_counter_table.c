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
struct ib_device {int dummy; } ;
struct ib_class_port_info {int capability_mask; } ;
struct attribute_group {int dummy; } ;
typedef  int /*<<< orphan*/  cpi ;

/* Variables and functions */
 int IB_PMA_CLASS_CAP_EXT_WIDTH ; 
 int IB_PMA_CLASS_CAP_EXT_WIDTH_NOIETF ; 
 int /*<<< orphan*/  IB_PMA_CLASS_PORT_INFO ; 
 scalar_t__ get_perf_mad (struct ib_device*,int,int /*<<< orphan*/ ,struct ib_class_port_info*,int,int) ; 
 struct attribute_group pma_group ; 
 struct attribute_group pma_group_ext ; 
 struct attribute_group pma_group_noietf ; 

__attribute__((used)) static struct attribute_group *get_counter_table(struct ib_device *dev,
						 int port_num)
{
	struct ib_class_port_info cpi;

	if (get_perf_mad(dev, port_num, IB_PMA_CLASS_PORT_INFO,
				&cpi, 40, sizeof(cpi)) >= 0) {
		if (cpi.capability_mask & IB_PMA_CLASS_CAP_EXT_WIDTH)
			/* We have extended counters */
			return &pma_group_ext;

		if (cpi.capability_mask & IB_PMA_CLASS_CAP_EXT_WIDTH_NOIETF)
			/* But not the IETF ones */
			return &pma_group_noietf;
	}

	/* Fall back to normal counters */
	return &pma_group;
}