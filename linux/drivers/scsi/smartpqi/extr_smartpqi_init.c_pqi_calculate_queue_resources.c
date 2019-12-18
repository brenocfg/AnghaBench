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
typedef  int u16 ;
struct pqi_sg_descriptor {int dummy; } ;
struct pqi_ctrl_info {int max_inbound_queues; int max_outbound_queues; int max_msix_vectors; int num_queue_groups; int max_hw_queue_index; int max_inbound_iu_length; int max_inbound_iu_length_per_firmware; int max_elements_per_iq; int max_elements_per_oq; int num_elements_per_iq; int num_elements_per_oq; scalar_t__ max_sg_per_iu; } ;

/* Variables and functions */
 scalar_t__ PQI_MAX_EMBEDDED_SG_DESCRIPTORS ; 
 int PQI_MAX_QUEUE_GROUPS ; 
 int PQI_OPERATIONAL_IQ_ELEMENT_LENGTH ; 
 int min (int,int) ; 
 int num_online_cpus () ; 
 scalar_t__ reset_devices ; 

__attribute__((used)) static void pqi_calculate_queue_resources(struct pqi_ctrl_info *ctrl_info)
{
	int num_queue_groups;
	u16 num_elements_per_iq;
	u16 num_elements_per_oq;

	if (reset_devices) {
		num_queue_groups = 1;
	} else {
		int num_cpus;
		int max_queue_groups;

		max_queue_groups = min(ctrl_info->max_inbound_queues / 2,
			ctrl_info->max_outbound_queues - 1);
		max_queue_groups = min(max_queue_groups, PQI_MAX_QUEUE_GROUPS);

		num_cpus = num_online_cpus();
		num_queue_groups = min(num_cpus, ctrl_info->max_msix_vectors);
		num_queue_groups = min(num_queue_groups, max_queue_groups);
	}

	ctrl_info->num_queue_groups = num_queue_groups;
	ctrl_info->max_hw_queue_index = num_queue_groups - 1;

	/*
	 * Make sure that the max. inbound IU length is an even multiple
	 * of our inbound element length.
	 */
	ctrl_info->max_inbound_iu_length =
		(ctrl_info->max_inbound_iu_length_per_firmware /
		PQI_OPERATIONAL_IQ_ELEMENT_LENGTH) *
		PQI_OPERATIONAL_IQ_ELEMENT_LENGTH;

	num_elements_per_iq =
		(ctrl_info->max_inbound_iu_length /
		PQI_OPERATIONAL_IQ_ELEMENT_LENGTH);

	/* Add one because one element in each queue is unusable. */
	num_elements_per_iq++;

	num_elements_per_iq = min(num_elements_per_iq,
		ctrl_info->max_elements_per_iq);

	num_elements_per_oq = ((num_elements_per_iq - 1) * 2) + 1;
	num_elements_per_oq = min(num_elements_per_oq,
		ctrl_info->max_elements_per_oq);

	ctrl_info->num_elements_per_iq = num_elements_per_iq;
	ctrl_info->num_elements_per_oq = num_elements_per_oq;

	ctrl_info->max_sg_per_iu =
		((ctrl_info->max_inbound_iu_length -
		PQI_OPERATIONAL_IQ_ELEMENT_LENGTH) /
		sizeof(struct pqi_sg_descriptor)) +
		PQI_MAX_EMBEDDED_SG_DESCRIPTORS;
}