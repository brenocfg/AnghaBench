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
struct pnp_dev {int flags; int /*<<< orphan*/  number; } ;
struct pnp_bios_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_node_size; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PNPBIOS_NO_DISABLE ; 
 scalar_t__ PNPMODE_DYNAMIC ; 
 int /*<<< orphan*/  kfree (struct pnp_bios_node*) ; 
 struct pnp_bios_node* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ node_info ; 
 scalar_t__ pnp_bios_get_dev_node (int /*<<< orphan*/ *,char,struct pnp_bios_node*) ; 
 int pnp_bios_set_dev_node (int /*<<< orphan*/ ,char,struct pnp_bios_node*) ; 
 int /*<<< orphan*/  pnpbios_is_dynamic (struct pnp_dev*) ; 
 int /*<<< orphan*/  pnpbios_zero_data_stream (struct pnp_bios_node*) ; 

__attribute__((used)) static int pnpbios_disable_resources(struct pnp_dev *dev)
{
	struct pnp_bios_node *node;
	u8 nodenum = dev->number;
	int ret;

	if (dev->flags & PNPBIOS_NO_DISABLE || !pnpbios_is_dynamic(dev))
		return -EPERM;

	node = kzalloc(node_info.max_node_size, GFP_KERNEL);
	if (!node)
		return -ENOMEM;

	if (pnp_bios_get_dev_node(&nodenum, (char)PNPMODE_DYNAMIC, node)) {
		kfree(node);
		return -ENODEV;
	}
	pnpbios_zero_data_stream(node);

	ret = pnp_bios_set_dev_node(dev->number, (char)PNPMODE_DYNAMIC, node);
	kfree(node);
	if (ret > 0)
		ret = -1;
	return ret;
}