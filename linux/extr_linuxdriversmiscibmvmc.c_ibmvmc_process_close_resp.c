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
struct ibmvmc_crq_msg {unsigned char hmc_index; scalar_t__ status; } ;
struct crq_server_adapter {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned char max_hmc_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/ * hmcs ; 
 TYPE_1__ ibmvmc ; 
 int /*<<< orphan*/  ibmvmc_reset (struct crq_server_adapter*,int) ; 
 int /*<<< orphan*/  ibmvmc_return_hmc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ibmvmc_process_close_resp(struct ibmvmc_crq_msg *crq,
				      struct crq_server_adapter *adapter)
{
	unsigned char hmc_index;

	hmc_index = crq->hmc_index;
	if (hmc_index > ibmvmc.max_hmc_index) {
		ibmvmc_reset(adapter, false);
		return;
	}

	if (crq->status) {
		dev_warn(adapter->dev, "close_resp: failed - status 0x%x\n",
			 crq->status);
		ibmvmc_reset(adapter, false);
		return;
	}

	ibmvmc_return_hmc(&hmcs[hmc_index], false);
}