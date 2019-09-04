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
struct TYPE_2__ {int /*<<< orphan*/  map_id; int /*<<< orphan*/  cmd; int /*<<< orphan*/  first; } ;
union ibmvnic_crq {TYPE_1__ request_unmap; } ;
typedef  int /*<<< orphan*/  u8 ;
struct ibmvnic_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  crq ;

/* Variables and functions */
 int /*<<< orphan*/  IBMVNIC_CRQ_CMD ; 
 int /*<<< orphan*/  REQUEST_UNMAP ; 
 int ibmvnic_send_crq (struct ibmvnic_adapter*,union ibmvnic_crq*) ; 
 int /*<<< orphan*/  memset (union ibmvnic_crq*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int send_request_unmap(struct ibmvnic_adapter *adapter, u8 map_id)
{
	union ibmvnic_crq crq;

	memset(&crq, 0, sizeof(crq));
	crq.request_unmap.first = IBMVNIC_CRQ_CMD;
	crq.request_unmap.cmd = REQUEST_UNMAP;
	crq.request_unmap.map_id = map_id;
	return ibmvnic_send_crq(adapter, &crq);
}