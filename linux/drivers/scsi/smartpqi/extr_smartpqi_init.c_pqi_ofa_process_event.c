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
typedef  scalar_t__ u16 ;
struct pqi_event {int /*<<< orphan*/  ofa_cancel_reason; int /*<<< orphan*/  ofa_bytes_requested; int /*<<< orphan*/  event_id; } ;
struct pqi_ctrl_info {int /*<<< orphan*/  ofa_mutex; int /*<<< orphan*/  ctrl_id; TYPE_1__* pci_dev; scalar_t__ soft_reset_handshake_supported; } ;
typedef  enum pqi_soft_reset_status { ____Placeholder_pqi_soft_reset_status } pqi_soft_reset_status ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PQI_EVENT_OFA_CANCELLED ; 
 scalar_t__ PQI_EVENT_OFA_MEMORY_ALLOCATION ; 
 scalar_t__ PQI_EVENT_OFA_QUIESCE ; 
 int RESET_INITIATE_FIRMWARE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pqi_acknowledge_event (struct pqi_ctrl_info*,struct pqi_event*) ; 
 int /*<<< orphan*/  pqi_ofa_ctrl_quiesce (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_ofa_free_host_buffer (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_ofa_host_memory_update (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_ofa_setup_host_buffer (struct pqi_ctrl_info*,int /*<<< orphan*/ ) ; 
 int pqi_poll_for_soft_reset_status (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_process_soft_reset (struct pqi_ctrl_info*,int) ; 

__attribute__((used)) static void pqi_ofa_process_event(struct pqi_ctrl_info *ctrl_info,
	struct pqi_event *event)
{
	u16 event_id;
	enum pqi_soft_reset_status status;

	event_id = get_unaligned_le16(&event->event_id);

	mutex_lock(&ctrl_info->ofa_mutex);

	if (event_id == PQI_EVENT_OFA_QUIESCE) {
		dev_info(&ctrl_info->pci_dev->dev,
			 "Received Online Firmware Activation quiesce event for controller %u\n",
			 ctrl_info->ctrl_id);
		pqi_ofa_ctrl_quiesce(ctrl_info);
		pqi_acknowledge_event(ctrl_info, event);
		if (ctrl_info->soft_reset_handshake_supported) {
			status = pqi_poll_for_soft_reset_status(ctrl_info);
			pqi_process_soft_reset(ctrl_info, status);
		} else {
			pqi_process_soft_reset(ctrl_info,
					RESET_INITIATE_FIRMWARE);
		}

	} else if (event_id == PQI_EVENT_OFA_MEMORY_ALLOCATION) {
		pqi_acknowledge_event(ctrl_info, event);
		pqi_ofa_setup_host_buffer(ctrl_info,
			le32_to_cpu(event->ofa_bytes_requested));
		pqi_ofa_host_memory_update(ctrl_info);
	} else if (event_id == PQI_EVENT_OFA_CANCELLED) {
		pqi_ofa_free_host_buffer(ctrl_info);
		pqi_acknowledge_event(ctrl_info, event);
		dev_info(&ctrl_info->pci_dev->dev,
			 "Online Firmware Activation(%u) cancel reason : %u\n",
			 ctrl_info->ctrl_id, event->ofa_cancel_reason);
	}

	mutex_unlock(&ctrl_info->ofa_mutex);
}