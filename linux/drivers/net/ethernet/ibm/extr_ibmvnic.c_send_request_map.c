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
struct TYPE_2__ {void* len; void* ioba; int /*<<< orphan*/  map_id; int /*<<< orphan*/  cmd; int /*<<< orphan*/  first; } ;
union ibmvnic_crq {TYPE_1__ request_map; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ibmvnic_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  crq ;

/* Variables and functions */
 int /*<<< orphan*/  IBMVNIC_CRQ_CMD ; 
 int /*<<< orphan*/  REQUEST_MAP ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int ibmvnic_send_crq (struct ibmvnic_adapter*,union ibmvnic_crq*) ; 
 int /*<<< orphan*/  memset (union ibmvnic_crq*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int send_request_map(struct ibmvnic_adapter *adapter, dma_addr_t addr,
			    u32 len, u8 map_id)
{
	union ibmvnic_crq crq;

	memset(&crq, 0, sizeof(crq));
	crq.request_map.first = IBMVNIC_CRQ_CMD;
	crq.request_map.cmd = REQUEST_MAP;
	crq.request_map.map_id = map_id;
	crq.request_map.ioba = cpu_to_be32(addr);
	crq.request_map.len = cpu_to_be32(len);
	return ibmvnic_send_crq(adapter, &crq);
}