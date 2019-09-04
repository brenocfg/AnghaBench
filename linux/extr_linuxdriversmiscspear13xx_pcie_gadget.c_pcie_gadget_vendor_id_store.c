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
typedef  int /*<<< orphan*/  ulong ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_VENDOR_ID ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spear_dbi_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_target (struct config_item*) ; 

__attribute__((used)) static ssize_t pcie_gadget_vendor_id_store(struct config_item *item,
		const char *buf, size_t count)
{
	ulong id;
	int ret;

	ret = kstrtoul(buf, 0, &id);
	if (ret)
		return ret;

	spear_dbi_write_reg(to_target(item), PCI_VENDOR_ID, 2, id);

	return count;
}