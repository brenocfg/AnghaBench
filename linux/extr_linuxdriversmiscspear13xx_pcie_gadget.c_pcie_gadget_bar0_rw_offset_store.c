#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int bar0_rw_offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* to_target (struct config_item*) ; 

__attribute__((used)) static ssize_t pcie_gadget_bar0_rw_offset_store(struct config_item *item,
		const char *buf, size_t count)
{
	ulong offset;
	int ret;

	ret = kstrtoul(buf, 0, &offset);
	if (ret)
		return ret;

	if (offset % 4)
		return -EINVAL;

	to_target(item)->bar0_rw_offset = offset;

	return count;
}