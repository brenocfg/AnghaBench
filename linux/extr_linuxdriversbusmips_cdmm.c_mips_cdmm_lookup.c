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
struct mips_cdmm_device_id {scalar_t__ type; } ;
struct mips_cdmm_device {scalar_t__ type; } ;

/* Variables and functions */

__attribute__((used)) static const struct mips_cdmm_device_id *
mips_cdmm_lookup(const struct mips_cdmm_device_id *table,
		 struct mips_cdmm_device *dev)
{
	int ret = 0;

	for (; table->type; ++table) {
		ret = (dev->type == table->type);
		if (ret)
			break;
	}

	return ret ? table : NULL;
}