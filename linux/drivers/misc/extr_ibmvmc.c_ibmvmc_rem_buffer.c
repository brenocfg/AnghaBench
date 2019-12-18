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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ibmvmc_crq_msg {size_t hmc_session; size_t hmc_index; } ;
struct ibmvmc_buffer {int /*<<< orphan*/  dma_addr_local; int /*<<< orphan*/  real_addr_local; scalar_t__ valid; int /*<<< orphan*/  id; } ;
struct crq_server_adapter {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {size_t max_hmc_index; int /*<<< orphan*/  max_mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMC_INVALID_BUFFER_ID ; 
 int /*<<< orphan*/  VMC_MSG_INVALID_HMC_INDEX ; 
 int /*<<< orphan*/  VMC_MSG_NO_BUFFER ; 
 int /*<<< orphan*/  VMC_MSG_SUCCESS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  free_dma_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* hmcs ; 
 TYPE_1__ ibmvmc ; 
 struct ibmvmc_buffer* ibmvmc_get_free_hmc_buffer (struct crq_server_adapter*,size_t) ; 
 int /*<<< orphan*/  ibmvmc_send_rem_buffer_resp (struct crq_server_adapter*,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ibmvmc_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  to_vio_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ibmvmc_rem_buffer(struct crq_server_adapter *adapter,
			     struct ibmvmc_crq_msg *crq)
{
	struct ibmvmc_buffer *buffer;
	u8 hmc_index;
	u8 hmc_session;
	u16 buffer_id = 0;
	unsigned long flags;
	int rc = 0;

	if (!crq)
		return -1;

	hmc_session = crq->hmc_session;
	hmc_index = crq->hmc_index;

	if (hmc_index > ibmvmc.max_hmc_index) {
		dev_warn(adapter->dev, "rem_buffer: invalid hmc_index = 0x%x\n",
			 hmc_index);
		ibmvmc_send_rem_buffer_resp(adapter, VMC_MSG_INVALID_HMC_INDEX,
					    hmc_session, hmc_index, buffer_id);
		return -1;
	}

	spin_lock_irqsave(&hmcs[hmc_index].lock, flags);
	buffer = ibmvmc_get_free_hmc_buffer(adapter, hmc_index);
	if (!buffer) {
		dev_info(adapter->dev, "rem_buffer: no buffer to remove\n");
		spin_unlock_irqrestore(&hmcs[hmc_index].lock, flags);
		ibmvmc_send_rem_buffer_resp(adapter, VMC_MSG_NO_BUFFER,
					    hmc_session, hmc_index,
					    VMC_INVALID_BUFFER_ID);
		return -1;
	}

	buffer_id = buffer->id;

	if (buffer->valid)
		free_dma_buffer(to_vio_dev(adapter->dev),
				ibmvmc.max_mtu,
				buffer->real_addr_local,
				buffer->dma_addr_local);

	memset(buffer, 0, sizeof(struct ibmvmc_buffer));
	spin_unlock_irqrestore(&hmcs[hmc_index].lock, flags);

	dev_dbg(adapter->dev, "rem_buffer: removed buffer 0x%x.\n", buffer_id);
	ibmvmc_send_rem_buffer_resp(adapter, VMC_MSG_SUCCESS, hmc_session,
				    hmc_index, buffer_id);

	return rc;
}