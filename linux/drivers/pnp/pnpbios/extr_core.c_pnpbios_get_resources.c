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
typedef  int /*<<< orphan*/  u8 ;
struct pnp_dev {int /*<<< orphan*/  active; int /*<<< orphan*/  dev; int /*<<< orphan*/  number; } ;
struct pnp_bios_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_node_size; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PNPMODE_DYNAMIC ; 
 int /*<<< orphan*/  kfree (struct pnp_bios_node*) ; 
 struct pnp_bios_node* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ node_info ; 
 scalar_t__ pnp_bios_get_dev_node (int /*<<< orphan*/ *,char,struct pnp_bios_node*) ; 
 int /*<<< orphan*/  pnp_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pnp_is_active (struct pnp_dev*) ; 
 int /*<<< orphan*/  pnpbios_is_dynamic (struct pnp_dev*) ; 
 int /*<<< orphan*/  pnpbios_read_resources_from_node (struct pnp_dev*,struct pnp_bios_node*) ; 

__attribute__((used)) static int pnpbios_get_resources(struct pnp_dev *dev)
{
	u8 nodenum = dev->number;
	struct pnp_bios_node *node;

	if (!pnpbios_is_dynamic(dev))
		return -EPERM;

	pnp_dbg(&dev->dev, "get resources\n");
	node = kzalloc(node_info.max_node_size, GFP_KERNEL);
	if (!node)
		return -1;
	if (pnp_bios_get_dev_node(&nodenum, (char)PNPMODE_DYNAMIC, node)) {
		kfree(node);
		return -ENODEV;
	}
	pnpbios_read_resources_from_node(dev, node);
	dev->active = pnp_is_active(dev);
	kfree(node);
	return 0;
}