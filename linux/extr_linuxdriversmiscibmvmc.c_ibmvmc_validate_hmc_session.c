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
struct ibmvmc_crq_msg {unsigned char hmc_index; int /*<<< orphan*/  hmc_session; } ;
struct crq_server_adapter {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  session; } ;
struct TYPE_3__ {unsigned char max_hmc_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* hmcs ; 
 TYPE_1__ ibmvmc ; 

__attribute__((used)) static int ibmvmc_validate_hmc_session(struct crq_server_adapter *adapter,
				       struct ibmvmc_crq_msg *crq)
{
	unsigned char hmc_index;

	hmc_index = crq->hmc_index;

	if (crq->hmc_session == 0)
		return 0;

	if (hmc_index > ibmvmc.max_hmc_index)
		return -1;

	if (hmcs[hmc_index].session != crq->hmc_session) {
		dev_warn(adapter->dev, "Drop, bad session: expected 0x%x, recv 0x%x\n",
			 hmcs[hmc_index].session, crq->hmc_session);
		return -1;
	}

	return 0;
}