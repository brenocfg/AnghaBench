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
typedef  scalar_t__ u32 ;
struct octeon_soft_command {scalar_t__ ctxptr; } ;
struct octeon_device {TYPE_1__* pci_dev; } ;
struct liquidio_rx_ctl_context {int /*<<< orphan*/  wc; int /*<<< orphan*/  cond; int /*<<< orphan*/  octeon_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVM_CAST64 (scalar_t__) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct octeon_device* lio_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void rx_ctl_callback(struct octeon_device *oct,
			    u32 status, void *buf)
{
	struct octeon_soft_command *sc = (struct octeon_soft_command *)buf;
	struct liquidio_rx_ctl_context *ctx;

	ctx  = (struct liquidio_rx_ctl_context *)sc->ctxptr;

	oct = lio_get_device(ctx->octeon_id);
	if (status)
		dev_err(&oct->pci_dev->dev, "rx ctl instruction failed. Status: %llx\n",
			CVM_CAST64(status));
	WRITE_ONCE(ctx->cond, 1);

	/* This barrier is required to be sure that the response has been
	 * written fully before waking up the handler
	 */
	wmb();

	wake_up_interruptible(&ctx->wc);
}