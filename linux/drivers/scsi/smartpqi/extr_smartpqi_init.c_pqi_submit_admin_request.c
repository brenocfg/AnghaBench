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
struct pqi_general_admin_request {int dummy; } ;
struct pqi_admin_queues {int iq_pi_copy; int /*<<< orphan*/  iq_pi; void* iq_element_array; } ;
struct pqi_ctrl_info {struct pqi_admin_queues admin_queues; } ;
typedef  int pqi_index_t ;

/* Variables and functions */
 int PQI_ADMIN_IQ_ELEMENT_LENGTH ; 
 int PQI_ADMIN_IQ_NUM_ELEMENTS ; 
 int /*<<< orphan*/  memcpy (void*,struct pqi_general_admin_request*,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pqi_submit_admin_request(struct pqi_ctrl_info *ctrl_info,
	struct pqi_general_admin_request *request)
{
	struct pqi_admin_queues *admin_queues;
	void *next_element;
	pqi_index_t iq_pi;

	admin_queues = &ctrl_info->admin_queues;
	iq_pi = admin_queues->iq_pi_copy;

	next_element = admin_queues->iq_element_array +
		(iq_pi * PQI_ADMIN_IQ_ELEMENT_LENGTH);

	memcpy(next_element, request, sizeof(*request));

	iq_pi = (iq_pi + 1) % PQI_ADMIN_IQ_NUM_ELEMENTS;
	admin_queues->iq_pi_copy = iq_pi;

	/*
	 * This write notifies the controller that an IU is available to be
	 * processed.
	 */
	writel(iq_pi, admin_queues->iq_pi);
}