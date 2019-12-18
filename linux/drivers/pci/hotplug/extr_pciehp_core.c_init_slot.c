#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hotplug_slot_ops {int /*<<< orphan*/  set_attention_status; int /*<<< orphan*/  get_attention_status; int /*<<< orphan*/  get_latch_status; int /*<<< orphan*/  reset_slot; int /*<<< orphan*/  get_adapter_status; int /*<<< orphan*/  get_power_status; int /*<<< orphan*/  disable_slot; int /*<<< orphan*/  enable_slot; } ;
struct TYPE_6__ {struct hotplug_slot_ops* ops; } ;
struct controller {TYPE_2__* pcie; TYPE_3__ hotplug_slot; } ;
struct TYPE_5__ {TYPE_1__* port; } ;
struct TYPE_4__ {int /*<<< orphan*/  subordinate; scalar_t__ hotplug_user_indicators; } ;

/* Variables and functions */
 scalar_t__ ATTN_LED (struct controller*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MRL_SENS (struct controller*) ; 
 int PSN (struct controller*) ; 
 int SLOT_NAME_SIZE ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*,int) ; 
 int /*<<< orphan*/  get_adapter_status ; 
 int /*<<< orphan*/  get_latch_status ; 
 int /*<<< orphan*/  get_power_status ; 
 int /*<<< orphan*/  kfree (struct hotplug_slot_ops*) ; 
 struct hotplug_slot_ops* kzalloc (int,int /*<<< orphan*/ ) ; 
 int pci_hp_initialize (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pciehp_get_attention_status ; 
 int /*<<< orphan*/  pciehp_get_raw_indicator_status ; 
 int /*<<< orphan*/  pciehp_reset_slot ; 
 int /*<<< orphan*/  pciehp_set_raw_indicator_status ; 
 int /*<<< orphan*/  pciehp_sysfs_disable_slot ; 
 int /*<<< orphan*/  pciehp_sysfs_enable_slot ; 
 int /*<<< orphan*/  set_attention_status ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int init_slot(struct controller *ctrl)
{
	struct hotplug_slot_ops *ops;
	char name[SLOT_NAME_SIZE];
	int retval;

	/* Setup hotplug slot ops */
	ops = kzalloc(sizeof(*ops), GFP_KERNEL);
	if (!ops)
		return -ENOMEM;

	ops->enable_slot = pciehp_sysfs_enable_slot;
	ops->disable_slot = pciehp_sysfs_disable_slot;
	ops->get_power_status = get_power_status;
	ops->get_adapter_status = get_adapter_status;
	ops->reset_slot = pciehp_reset_slot;
	if (MRL_SENS(ctrl))
		ops->get_latch_status = get_latch_status;
	if (ATTN_LED(ctrl)) {
		ops->get_attention_status = pciehp_get_attention_status;
		ops->set_attention_status = set_attention_status;
	} else if (ctrl->pcie->port->hotplug_user_indicators) {
		ops->get_attention_status = pciehp_get_raw_indicator_status;
		ops->set_attention_status = pciehp_set_raw_indicator_status;
	}

	/* register this slot with the hotplug pci core */
	ctrl->hotplug_slot.ops = ops;
	snprintf(name, SLOT_NAME_SIZE, "%u", PSN(ctrl));

	retval = pci_hp_initialize(&ctrl->hotplug_slot,
				   ctrl->pcie->port->subordinate, 0, name);
	if (retval) {
		ctrl_err(ctrl, "pci_hp_initialize failed: error %d\n", retval);
		kfree(ops);
	}
	return retval;
}