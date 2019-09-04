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
struct vio_dev {int dummy; } ;
struct ibmvmc_hmc {int /*<<< orphan*/  lock; int /*<<< orphan*/ * queue_outbound_msgs; struct ibmvmc_buffer* buffer; scalar_t__ queue_tail; scalar_t__ queue_head; int /*<<< orphan*/  state; scalar_t__ index; struct crq_server_adapter* adapter; struct ibmvmc_file_session* file_session; } ;
struct ibmvmc_file_session {scalar_t__ valid; } ;
struct ibmvmc_buffer {int /*<<< orphan*/  dma_addr_local; int /*<<< orphan*/  real_addr_local; scalar_t__ valid; } ;
struct crq_server_adapter {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_mtu; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  VMC_INVALID_BUFFER_ID ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  free_dma_buffer (struct vio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmhmc_state_free ; 
 TYPE_1__ ibmvmc ; 
 unsigned long ibmvmc_max_buf_pool_size ; 
 int /*<<< orphan*/  ibmvmc_read_wait ; 
 int /*<<< orphan*/  memset (struct ibmvmc_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vio_dev* to_vio_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ibmvmc_return_hmc(struct ibmvmc_hmc *hmc, bool release_readers)
{
	struct ibmvmc_buffer *buffer;
	struct crq_server_adapter *adapter;
	struct vio_dev *vdev;
	unsigned long i;
	unsigned long flags;

	if (!hmc || !hmc->adapter)
		return -EIO;

	if (release_readers) {
		if (hmc->file_session) {
			struct ibmvmc_file_session *session = hmc->file_session;

			session->valid = 0;
			wake_up_interruptible(&ibmvmc_read_wait);
		}
	}

	adapter = hmc->adapter;
	vdev = to_vio_dev(adapter->dev);

	spin_lock_irqsave(&hmc->lock, flags);
	hmc->index = 0;
	hmc->state = ibmhmc_state_free;
	hmc->queue_head = 0;
	hmc->queue_tail = 0;
	buffer = hmc->buffer;
	for (i = 0; i < ibmvmc_max_buf_pool_size; i++) {
		if (buffer[i].valid) {
			free_dma_buffer(vdev,
					ibmvmc.max_mtu,
					buffer[i].real_addr_local,
					buffer[i].dma_addr_local);
			dev_dbg(adapter->dev, "Forgot buffer id 0x%lx\n", i);
		}
		memset(&buffer[i], 0, sizeof(struct ibmvmc_buffer));

		hmc->queue_outbound_msgs[i] = VMC_INVALID_BUFFER_ID;
	}

	spin_unlock_irqrestore(&hmc->lock, flags);

	return 0;
}