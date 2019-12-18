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
struct esas2r_vda_ae {int /*<<< orphan*/  vda_ae; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus_number; int /*<<< orphan*/  signature; } ;
struct esas2r_fw_event_work {int type; int /*<<< orphan*/  work; int /*<<< orphan*/  list; struct esas2r_adapter* a; int /*<<< orphan*/ * data; } ;
struct esas2r_adapter {int /*<<< orphan*/  fw_event_lock; int /*<<< orphan*/  fw_event_q; int /*<<< orphan*/  fw_event_list; TYPE_2__* pcid; } ;
typedef  enum fw_event_type { ____Placeholder_fw_event_type } fw_event_type ;
struct TYPE_4__ {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESAS2R_LOG_WARN ; 
 int /*<<< orphan*/  ESAS2R_VDA_EVENT_SIG ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_firmware_event_work ; 
 int /*<<< orphan*/  esas2r_log (int /*<<< orphan*/ ,char*) ; 
 int fw_event_vda_ae ; 
 struct esas2r_fw_event_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void esas2r_queue_fw_event(struct esas2r_adapter *a,
			   enum fw_event_type type,
			   void *data,
			   int data_sz)
{
	struct esas2r_fw_event_work *fw_event;
	unsigned long flags;

	fw_event = kzalloc(sizeof(struct esas2r_fw_event_work), GFP_ATOMIC);
	if (!fw_event) {
		esas2r_log(ESAS2R_LOG_WARN,
			   "esas2r_queue_fw_event failed to alloc");
		return;
	}

	if (type == fw_event_vda_ae) {
		struct esas2r_vda_ae *ae =
			(struct esas2r_vda_ae *)fw_event->data;

		ae->signature = ESAS2R_VDA_EVENT_SIG;
		ae->bus_number = a->pcid->bus->number;
		ae->devfn = a->pcid->devfn;
		memcpy(&ae->vda_ae, data, sizeof(ae->vda_ae));
	} else {
		memcpy(fw_event->data, data, data_sz);
	}

	fw_event->type = type;
	fw_event->a = a;

	spin_lock_irqsave(&a->fw_event_lock, flags);
	list_add_tail(&fw_event->list, &a->fw_event_list);
	INIT_DELAYED_WORK(&fw_event->work, esas2r_firmware_event_work);
	queue_delayed_work_on(
		smp_processor_id(), a->fw_event_q, &fw_event->work,
		msecs_to_jiffies(1));
	spin_unlock_irqrestore(&a->fw_event_lock, flags);
}