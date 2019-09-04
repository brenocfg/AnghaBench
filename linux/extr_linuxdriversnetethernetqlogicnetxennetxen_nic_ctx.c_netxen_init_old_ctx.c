#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nx_host_tx_ring {int num_desc; int /*<<< orphan*/  phys_addr; } ;
struct nx_host_sds_ring {int num_desc; int /*<<< orphan*/  phys_addr; } ;
struct nx_host_rds_ring {int num_desc; int /*<<< orphan*/  phys_addr; } ;
struct netxen_ring_ctx {void* sts_ring_count; TYPE_2__* sts_rings; void* sts_ring_size; void* sts_ring_addr; TYPE_1__* rcv_rings; void* cmd_ring_size; void* cmd_ring_addr; } ;
struct netxen_recv_context {int /*<<< orphan*/  phys_addr; struct nx_host_sds_ring* sds_rings; struct nx_host_rds_ring* rds_rings; struct netxen_ring_ctx* hwctx; } ;
struct netxen_adapter {int portnum; int max_rds_rings; int max_sds_rings; struct netxen_recv_context recv_ctx; struct nx_host_tx_ring* tx_ring; } ;
struct TYPE_4__ {int /*<<< orphan*/  msi_index; void* size; void* addr; } ;
struct TYPE_3__ {void* size; void* addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRB_CTX_ADDR_REG_HI (int) ; 
 int /*<<< orphan*/  CRB_CTX_ADDR_REG_LO (int) ; 
 int /*<<< orphan*/  CRB_CTX_SIGNATURE_REG (int) ; 
 int NETXEN_CTX_SIGNATURE ; 
 int NETXEN_CTX_SIGNATURE_V2 ; 
 int /*<<< orphan*/  NXWR32 (struct netxen_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int lower32 (int /*<<< orphan*/ ) ; 
 int upper32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
netxen_init_old_ctx(struct netxen_adapter *adapter)
{
	struct netxen_recv_context *recv_ctx;
	struct nx_host_rds_ring *rds_ring;
	struct nx_host_sds_ring *sds_ring;
	struct nx_host_tx_ring *tx_ring;
	int ring;
	int port = adapter->portnum;
	struct netxen_ring_ctx *hwctx;
	u32 signature;

	tx_ring = adapter->tx_ring;
	recv_ctx = &adapter->recv_ctx;
	hwctx = recv_ctx->hwctx;

	hwctx->cmd_ring_addr = cpu_to_le64(tx_ring->phys_addr);
	hwctx->cmd_ring_size = cpu_to_le32(tx_ring->num_desc);


	for (ring = 0; ring < adapter->max_rds_rings; ring++) {
		rds_ring = &recv_ctx->rds_rings[ring];

		hwctx->rcv_rings[ring].addr =
			cpu_to_le64(rds_ring->phys_addr);
		hwctx->rcv_rings[ring].size =
			cpu_to_le32(rds_ring->num_desc);
	}

	for (ring = 0; ring < adapter->max_sds_rings; ring++) {
		sds_ring = &recv_ctx->sds_rings[ring];

		if (ring == 0) {
			hwctx->sts_ring_addr = cpu_to_le64(sds_ring->phys_addr);
			hwctx->sts_ring_size = cpu_to_le32(sds_ring->num_desc);
		}
		hwctx->sts_rings[ring].addr = cpu_to_le64(sds_ring->phys_addr);
		hwctx->sts_rings[ring].size = cpu_to_le32(sds_ring->num_desc);
		hwctx->sts_rings[ring].msi_index = cpu_to_le16(ring);
	}
	hwctx->sts_ring_count = cpu_to_le32(adapter->max_sds_rings);

	signature = (adapter->max_sds_rings > 1) ?
		NETXEN_CTX_SIGNATURE_V2 : NETXEN_CTX_SIGNATURE;

	NXWR32(adapter, CRB_CTX_ADDR_REG_LO(port),
			lower32(recv_ctx->phys_addr));
	NXWR32(adapter, CRB_CTX_ADDR_REG_HI(port),
			upper32(recv_ctx->phys_addr));
	NXWR32(adapter, CRB_CTX_SIGNATURE_REG(port),
			signature | port);
	return 0;
}