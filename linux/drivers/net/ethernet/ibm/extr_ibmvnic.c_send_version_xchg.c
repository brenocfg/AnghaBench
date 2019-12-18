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
struct TYPE_2__ {int /*<<< orphan*/  version; int /*<<< orphan*/  cmd; int /*<<< orphan*/  first; } ;
union ibmvnic_crq {TYPE_1__ version_exchange; } ;
struct ibmvnic_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  crq ;

/* Variables and functions */
 int /*<<< orphan*/  IBMVNIC_CRQ_CMD ; 
 int /*<<< orphan*/  VERSION_EXCHANGE ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int ibmvnic_send_crq (struct ibmvnic_adapter*,union ibmvnic_crq*) ; 
 int /*<<< orphan*/  ibmvnic_version ; 
 int /*<<< orphan*/  memset (union ibmvnic_crq*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int send_version_xchg(struct ibmvnic_adapter *adapter)
{
	union ibmvnic_crq crq;

	memset(&crq, 0, sizeof(crq));
	crq.version_exchange.first = IBMVNIC_CRQ_CMD;
	crq.version_exchange.cmd = VERSION_EXCHANGE;
	crq.version_exchange.version = cpu_to_be16(ibmvnic_version);

	return ibmvnic_send_crq(adapter, &crq);
}