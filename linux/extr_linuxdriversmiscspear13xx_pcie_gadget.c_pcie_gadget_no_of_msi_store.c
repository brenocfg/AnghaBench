#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct config_item {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int requested_msi; } ;
struct TYPE_3__ {int /*<<< orphan*/  requested_msi; } ;

/* Variables and functions */
 TYPE_2__* config ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* to_target (struct config_item*) ; 

__attribute__((used)) static ssize_t pcie_gadget_no_of_msi_store(struct config_item *item,
		const char *buf, size_t count)
{
	int ret;

	ret = kstrtoul(buf, 0, &to_target(item)->requested_msi);
	if (ret)
		return ret;

	if (config->requested_msi > 32)
		config->requested_msi = 32;

	return count;
}