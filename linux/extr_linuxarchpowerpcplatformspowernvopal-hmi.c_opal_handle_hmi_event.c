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
struct opal_msg {int /*<<< orphan*/ * params; } ;
struct notifier_block {int dummy; } ;
struct OpalHmiEvtNode {int /*<<< orphan*/  list; int /*<<< orphan*/  hmi_evt; } ;
struct OpalHMIEvent {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned long OPAL_MSG_HMI_EVT ; 
 int /*<<< orphan*/  hmi_event_work ; 
 struct OpalHmiEvtNode* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct OpalHMIEvent*,int) ; 
 int /*<<< orphan*/  opal_hmi_evt_list ; 
 int /*<<< orphan*/  opal_hmi_evt_lock ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int opal_handle_hmi_event(struct notifier_block *nb,
			  unsigned long msg_type, void *msg)
{
	unsigned long flags;
	struct OpalHMIEvent *hmi_evt;
	struct opal_msg *hmi_msg = msg;
	struct OpalHmiEvtNode *msg_node;

	/* Sanity Checks */
	if (msg_type != OPAL_MSG_HMI_EVT)
		return 0;

	/* HMI event info starts from param[0] */
	hmi_evt = (struct OpalHMIEvent *)&hmi_msg->params[0];

	/* Delay the logging of HMI events to workqueue. */
	msg_node = kzalloc(sizeof(*msg_node), GFP_ATOMIC);
	if (!msg_node) {
		pr_err("HMI: out of memory, Opal message event not handled\n");
		return -ENOMEM;
	}
	memcpy(&msg_node->hmi_evt, hmi_evt, sizeof(*hmi_evt));

	spin_lock_irqsave(&opal_hmi_evt_lock, flags);
	list_add(&msg_node->list, &opal_hmi_evt_list);
	spin_unlock_irqrestore(&opal_hmi_evt_lock, flags);

	schedule_work(&hmi_event_work);
	return 0;
}