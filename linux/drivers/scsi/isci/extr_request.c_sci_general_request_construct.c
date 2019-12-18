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
struct isci_request {int post_context; scalar_t__ scu_status; int /*<<< orphan*/  sci_status; int /*<<< orphan*/  saved_rx_frame_index; int /*<<< orphan*/  protocol; struct isci_remote_device* target_device; int /*<<< orphan*/  sm; } ;
struct isci_remote_device {int dummy; } ;
struct isci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_PROTOCOL_NONE ; 
 int /*<<< orphan*/  SCI_REQ_INIT ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  SCU_INVALID_FRAME_INDEX ; 
 int /*<<< orphan*/  sci_init_sm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_request_state_table ; 

__attribute__((used)) static void
sci_general_request_construct(struct isci_host *ihost,
				   struct isci_remote_device *idev,
				   struct isci_request *ireq)
{
	sci_init_sm(&ireq->sm, sci_request_state_table, SCI_REQ_INIT);

	ireq->target_device = idev;
	ireq->protocol = SAS_PROTOCOL_NONE;
	ireq->saved_rx_frame_index = SCU_INVALID_FRAME_INDEX;

	ireq->sci_status   = SCI_SUCCESS;
	ireq->scu_status   = 0;
	ireq->post_context = 0xFFFFFFFF;
}