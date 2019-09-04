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
typedef  int u32 ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEVICE_ID ; 
 int /*<<< orphan*/  spear_dbi_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  to_target (struct config_item*) ; 

__attribute__((used)) static ssize_t pcie_gadget_device_id_show(struct config_item *item, char *buf)
{
	u32 id;

	spear_dbi_read_reg(to_target(item), PCI_DEVICE_ID, 2, &id);

	return sprintf(buf, "%x", id);
}