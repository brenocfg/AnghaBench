#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hotplug_slot {int /*<<< orphan*/ * ops; } ;
struct slot {int hp_slot; int number; int /*<<< orphan*/  wq; int /*<<< orphan*/  slot_list; int /*<<< orphan*/  presence_save; int /*<<< orphan*/  latch_save; int /*<<< orphan*/  attention_save; int /*<<< orphan*/  pwr_save; scalar_t__ device; int /*<<< orphan*/  bus; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; int /*<<< orphan*/  hpc_ops; struct controller* ctrl; struct hotplug_slot hotplug_slot; } ;
struct controller {int num_slots; int first_slot; int slot_num_inc; int /*<<< orphan*/  slot_list; TYPE_1__* pci_dev; int /*<<< orphan*/  slot_device_offset; int /*<<< orphan*/  hpc_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  number; } ;
struct TYPE_4__ {TYPE_2__* subordinate; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SLOT_NAME_SIZE ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ctrl_dbg (struct controller*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*,int) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_adapter_status (struct hotplug_slot*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_attention_status (struct hotplug_slot*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_latch_status (struct hotplug_slot*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_power_status (struct hotplug_slot*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct slot*) ; 
 struct slot* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_domain_nr (TYPE_2__*) ; 
 int pci_hp_register (struct hotplug_slot*,TYPE_2__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  shpchp_hotplug_slot_ops ; 
 int /*<<< orphan*/  shpchp_queue_pushbutton_work ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int init_slots(struct controller *ctrl)
{
	struct slot *slot;
	struct hotplug_slot *hotplug_slot;
	char name[SLOT_NAME_SIZE];
	int retval;
	int i;

	for (i = 0; i < ctrl->num_slots; i++) {
		slot = kzalloc(sizeof(*slot), GFP_KERNEL);
		if (!slot) {
			retval = -ENOMEM;
			goto error;
		}

		hotplug_slot = &slot->hotplug_slot;

		slot->hp_slot = i;
		slot->ctrl = ctrl;
		slot->bus = ctrl->pci_dev->subordinate->number;
		slot->device = ctrl->slot_device_offset + i;
		slot->hpc_ops = ctrl->hpc_ops;
		slot->number = ctrl->first_slot + (ctrl->slot_num_inc * i);

		slot->wq = alloc_workqueue("shpchp-%d", 0, 0, slot->number);
		if (!slot->wq) {
			retval = -ENOMEM;
			goto error_slot;
		}

		mutex_init(&slot->lock);
		INIT_DELAYED_WORK(&slot->work, shpchp_queue_pushbutton_work);

		/* register this slot with the hotplug pci core */
		snprintf(name, SLOT_NAME_SIZE, "%d", slot->number);
		hotplug_slot->ops = &shpchp_hotplug_slot_ops;

		ctrl_dbg(ctrl, "Registering domain:bus:dev=%04x:%02x:%02x hp_slot=%x sun=%x slot_device_offset=%x\n",
			 pci_domain_nr(ctrl->pci_dev->subordinate),
			 slot->bus, slot->device, slot->hp_slot, slot->number,
			 ctrl->slot_device_offset);
		retval = pci_hp_register(hotplug_slot,
				ctrl->pci_dev->subordinate, slot->device, name);
		if (retval) {
			ctrl_err(ctrl, "pci_hp_register failed with error %d\n",
				 retval);
			goto error_slotwq;
		}

		get_power_status(hotplug_slot, &slot->pwr_save);
		get_attention_status(hotplug_slot, &slot->attention_save);
		get_latch_status(hotplug_slot, &slot->latch_save);
		get_adapter_status(hotplug_slot, &slot->presence_save);

		list_add(&slot->slot_list, &ctrl->slot_list);
	}

	return 0;
error_slotwq:
	destroy_workqueue(slot->wq);
error_slot:
	kfree(slot);
error:
	return retval;
}