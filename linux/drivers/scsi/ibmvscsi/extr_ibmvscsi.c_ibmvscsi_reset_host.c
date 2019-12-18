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
struct ibmvscsi_host_data {int /*<<< orphan*/  work_wait_q; int /*<<< orphan*/  action; int /*<<< orphan*/  request_limit; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_ERROR ; 
 int /*<<< orphan*/  IBMVSCSI_HOST_ACTION_RESET ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  purge_requests (struct ibmvscsi_host_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_block_requests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ibmvscsi_reset_host(struct ibmvscsi_host_data *hostdata)
{
	scsi_block_requests(hostdata->host);
	atomic_set(&hostdata->request_limit, 0);

	purge_requests(hostdata, DID_ERROR);
	hostdata->action = IBMVSCSI_HOST_ACTION_RESET;
	wake_up(&hostdata->work_wait_q);
}