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
struct ibmvmc_crq_msg {int dummy; } ;
struct ibmvmc_admin_crq_msg {int max_hmc; int /*<<< orphan*/  pool_size; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  version; } ;
struct crq_server_adapter {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {void* max_hmc_index; void* max_buffer_pool_size; void* max_mtu; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int IBMVMC_PROTOCOL_VERSION ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,void*,void*,void*) ; 
 TYPE_1__ ibmvmc ; 
 int /*<<< orphan*/  ibmvmc_max_buf_pool_size ; 
 int /*<<< orphan*/  ibmvmc_max_hmcs ; 
 int /*<<< orphan*/  ibmvmc_max_mtu ; 
 int /*<<< orphan*/  ibmvmc_state_failed ; 
 int /*<<< orphan*/  ibmvmc_state_ready ; 
 void* min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  u16 ; 
 int /*<<< orphan*/  u32 ; 
 int /*<<< orphan*/  u8 ; 

__attribute__((used)) static void ibmvmc_process_capabilities(struct crq_server_adapter *adapter,
					struct ibmvmc_crq_msg *crqp)
{
	struct ibmvmc_admin_crq_msg *crq = (struct ibmvmc_admin_crq_msg *)crqp;

	if ((be16_to_cpu(crq->version) >> 8) !=
			(IBMVMC_PROTOCOL_VERSION >> 8)) {
		dev_err(adapter->dev, "init failed, incompatible versions 0x%x 0x%x\n",
			be16_to_cpu(crq->version),
			IBMVMC_PROTOCOL_VERSION);
		ibmvmc.state = ibmvmc_state_failed;
		return;
	}

	ibmvmc.max_mtu = min_t(u32, ibmvmc_max_mtu, be32_to_cpu(crq->max_mtu));
	ibmvmc.max_buffer_pool_size = min_t(u16, ibmvmc_max_buf_pool_size,
					    be16_to_cpu(crq->pool_size));
	ibmvmc.max_hmc_index = min_t(u8, ibmvmc_max_hmcs, crq->max_hmc) - 1;
	ibmvmc.state = ibmvmc_state_ready;

	dev_info(adapter->dev, "Capabilities: mtu=0x%x, pool_size=0x%x, max_hmc=0x%x\n",
		 ibmvmc.max_mtu, ibmvmc.max_buffer_pool_size,
		 ibmvmc.max_hmc_index);
}