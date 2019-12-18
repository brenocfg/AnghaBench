#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  buffer_id; } ;
struct ibmvmc_crq_msg {unsigned char hmc_index; scalar_t__ status; TYPE_1__ var2; } ;
struct crq_server_adapter {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {unsigned char max_hmc_index; unsigned short max_buffer_pool_size; } ;
struct TYPE_7__ {scalar_t__ state; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 unsigned short be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned short) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 TYPE_2__* hmcs ; 
 scalar_t__ ibmhmc_state_failed ; 
 scalar_t__ ibmhmc_state_opening ; 
 scalar_t__ ibmhmc_state_ready ; 
 TYPE_4__ ibmvmc ; 
 int /*<<< orphan*/  ibmvmc_free_hmc_buffer (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibmvmc_reset (struct crq_server_adapter*,int) ; 
 int /*<<< orphan*/  ibmvmc_return_hmc (TYPE_2__*,int) ; 

__attribute__((used)) static void ibmvmc_process_open_resp(struct ibmvmc_crq_msg *crq,
				     struct crq_server_adapter *adapter)
{
	unsigned char hmc_index;
	unsigned short buffer_id;

	hmc_index = crq->hmc_index;
	if (hmc_index > ibmvmc.max_hmc_index) {
		/* Why would PHYP give an index > max negotiated? */
		ibmvmc_reset(adapter, false);
		return;
	}

	if (crq->status) {
		dev_warn(adapter->dev, "open_resp: failed - status 0x%x\n",
			 crq->status);
		ibmvmc_return_hmc(&hmcs[hmc_index], false);
		return;
	}

	if (hmcs[hmc_index].state == ibmhmc_state_opening) {
		buffer_id = be16_to_cpu(crq->var2.buffer_id);
		if (buffer_id >= ibmvmc.max_buffer_pool_size) {
			dev_err(adapter->dev, "open_resp: invalid buffer_id = 0x%x\n",
				buffer_id);
			hmcs[hmc_index].state = ibmhmc_state_failed;
		} else {
			ibmvmc_free_hmc_buffer(&hmcs[hmc_index],
					       &hmcs[hmc_index].buffer[buffer_id]);
			hmcs[hmc_index].state = ibmhmc_state_ready;
			dev_dbg(adapter->dev, "open_resp: set hmc state = ready\n");
		}
	} else {
		dev_warn(adapter->dev, "open_resp: invalid hmc state (0x%x)\n",
			 hmcs[hmc_index].state);
	}
}