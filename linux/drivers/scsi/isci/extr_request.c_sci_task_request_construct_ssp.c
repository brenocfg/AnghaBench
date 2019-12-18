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
struct isci_request {int /*<<< orphan*/  sm; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_REQ_CONSTRUCTED ; 
 int SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_task_request_build_ssp_task_iu (struct isci_request*) ; 
 int /*<<< orphan*/  scu_ssp_task_request_construct_task_context (struct isci_request*) ; 

enum sci_status sci_task_request_construct_ssp(
	struct isci_request *ireq)
{
	/* Construct the SSP Task SCU Task Context */
	scu_ssp_task_request_construct_task_context(ireq);

	/* Fill in the SSP Task IU */
	sci_task_request_build_ssp_task_iu(ireq);

	sci_change_state(&ireq->sm, SCI_REQ_CONSTRUCTED);

	return SCI_SUCCESS;
}