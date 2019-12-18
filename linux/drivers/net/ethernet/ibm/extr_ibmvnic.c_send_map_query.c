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
union ibmvnic_crq {TYPE_1__ query_map; } ;
struct ibmvnic_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  crq ;

/* Variables and functions */
 int /*<<< orphan*/  IBMVNIC_CRQ_CMD ; 
 int /*<<< orphan*/  QUERY_MAP ; 
 int /*<<< orphan*/  ibmvnic_send_crq (struct ibmvnic_adapter*,union ibmvnic_crq*) ; 
 int /*<<< orphan*/  memset (union ibmvnic_crq*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void send_map_query(struct ibmvnic_adapter *adapter)
{
	union ibmvnic_crq crq;

	memset(&crq, 0, sizeof(crq));
	crq.query_map.first = IBMVNIC_CRQ_CMD;
	crq.query_map.cmd = QUERY_MAP;
	ibmvnic_send_crq(adapter, &crq);
}