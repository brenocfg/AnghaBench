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
struct sas_task {int /*<<< orphan*/  total_xfer_len; int /*<<< orphan*/  data_dir; } ;
struct isci_request {int /*<<< orphan*/  sm; int /*<<< orphan*/  protocol; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_PROTOCOL_SSP ; 
 int /*<<< orphan*/  SCI_REQ_CONSTRUCTED ; 
 int SCI_SUCCESS ; 
 struct sas_task* isci_request_access_task (struct isci_request*) ; 
 int /*<<< orphan*/  sci_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_io_request_build_ssp_command_iu (struct isci_request*) ; 
 int /*<<< orphan*/  scu_ssp_io_request_construct_task_context (struct isci_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum sci_status sci_io_request_construct_basic_ssp(struct isci_request *ireq)
{
	struct sas_task *task = isci_request_access_task(ireq);

	ireq->protocol = SAS_PROTOCOL_SSP;

	scu_ssp_io_request_construct_task_context(ireq,
						  task->data_dir,
						  task->total_xfer_len);

	sci_io_request_build_ssp_command_iu(ireq);

	sci_change_state(&ireq->sm, SCI_REQ_CONSTRUCTED);

	return SCI_SUCCESS;
}