#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ibmvmc_crq_msg {int valid; } ;
struct crq_server_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ibmvmc_crq_process (struct crq_server_adapter*,struct ibmvmc_crq_msg*) ; 
 int /*<<< orphan*/  ibmvmc_handle_crq_init (struct ibmvmc_crq_msg*,struct crq_server_adapter*) ; 
 int /*<<< orphan*/  ibmvmc_reset (struct crq_server_adapter*,int) ; 

__attribute__((used)) static void ibmvmc_handle_crq(struct ibmvmc_crq_msg *crq,
			      struct crq_server_adapter *adapter)
{
	switch (crq->valid) {
	case 0xC0:		/* initialization */
		ibmvmc_handle_crq_init(crq, adapter);
		break;
	case 0xFF:	/* Hypervisor telling us the connection is closed */
		dev_warn(adapter->dev, "CRQ recv: virtual adapter failed - resetting.\n");
		ibmvmc_reset(adapter, true);
		break;
	case 0x80:	/* real payload */
		ibmvmc_crq_process(adapter, crq);
		break;
	default:
		dev_warn(adapter->dev, "CRQ recv: unknown msg 0x%02x.\n",
			 crq->valid);
		break;
	}
}