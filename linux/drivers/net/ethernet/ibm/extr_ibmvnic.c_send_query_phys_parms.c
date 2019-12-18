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
struct TYPE_2__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/  first; } ;
union ibmvnic_crq {TYPE_1__ query_phys_parms; } ;
struct ibmvnic_adapter {scalar_t__ fw_done_rc; int /*<<< orphan*/  fw_done; } ;
typedef  int /*<<< orphan*/  crq ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IBMVNIC_CRQ_CMD ; 
 int /*<<< orphan*/  QUERY_PHYS_PARMS ; 
 int ibmvnic_send_crq (struct ibmvnic_adapter*,union ibmvnic_crq*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (union ibmvnic_crq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int send_query_phys_parms(struct ibmvnic_adapter *adapter)
{
	union ibmvnic_crq crq;
	int rc;

	memset(&crq, 0, sizeof(crq));
	crq.query_phys_parms.first = IBMVNIC_CRQ_CMD;
	crq.query_phys_parms.cmd = QUERY_PHYS_PARMS;
	init_completion(&adapter->fw_done);
	rc = ibmvnic_send_crq(adapter, &crq);
	if (rc)
		return rc;
	wait_for_completion(&adapter->fw_done);
	return adapter->fw_done_rc ? -EIO : 0;
}