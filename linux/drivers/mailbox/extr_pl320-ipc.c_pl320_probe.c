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
struct amba_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;
struct amba_device {int /*<<< orphan*/  dev; int /*<<< orphan*/ * irq; TYPE_1__ res; } ;

/* Variables and functions */
 int /*<<< orphan*/  A9_SOURCE ; 
 int CHAN_MASK (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int IPCMxDSET (int /*<<< orphan*/ ) ; 
 int IPCMxMSET (int /*<<< orphan*/ ) ; 
 int IPCMxSEND (int /*<<< orphan*/ ) ; 
 int IPCMxSOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC_RX_MBOX ; 
 int /*<<< orphan*/  IPC_TX_MBOX ; 
 int /*<<< orphan*/  M3_SOURCE ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ipc_base ; 
 int /*<<< orphan*/  ipc_handler ; 
 int /*<<< orphan*/  ipc_irq ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pl320_probe(struct amba_device *adev, const struct amba_id *id)
{
	int ret;

	ipc_base = ioremap(adev->res.start, resource_size(&adev->res));
	if (ipc_base == NULL)
		return -ENOMEM;

	writel_relaxed(0, ipc_base + IPCMxSEND(IPC_TX_MBOX));

	ipc_irq = adev->irq[0];
	ret = request_irq(ipc_irq, ipc_handler, 0, dev_name(&adev->dev), NULL);
	if (ret < 0)
		goto err;

	/* Init slow mailbox */
	writel_relaxed(CHAN_MASK(A9_SOURCE),
		       ipc_base + IPCMxSOURCE(IPC_TX_MBOX));
	writel_relaxed(CHAN_MASK(M3_SOURCE),
		       ipc_base + IPCMxDSET(IPC_TX_MBOX));
	writel_relaxed(CHAN_MASK(M3_SOURCE) | CHAN_MASK(A9_SOURCE),
		       ipc_base + IPCMxMSET(IPC_TX_MBOX));

	/* Init receive mailbox */
	writel_relaxed(CHAN_MASK(M3_SOURCE),
		       ipc_base + IPCMxSOURCE(IPC_RX_MBOX));
	writel_relaxed(CHAN_MASK(A9_SOURCE),
		       ipc_base + IPCMxDSET(IPC_RX_MBOX));
	writel_relaxed(CHAN_MASK(M3_SOURCE) | CHAN_MASK(A9_SOURCE),
		       ipc_base + IPCMxMSET(IPC_RX_MBOX));

	return 0;
err:
	iounmap(ipc_base);
	return ret;
}