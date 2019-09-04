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
struct liquidio_if_cfg_context {int /*<<< orphan*/  wc; int /*<<< orphan*/  cond; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVM_CAST64 (scalar_t__) ; 
 int /*<<< orphan*/  LIO_CHANGE_MTU_FAIL ; 
 int /*<<< orphan*/  LIO_CHANGE_MTU_SUCCESS ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void liquidio_change_mtu_completion(struct octeon_device *oct,
					   u32 status, void *buf)
{
	struct octeon_soft_command *sc = (struct octeon_soft_command *)buf;
	struct liquidio_if_cfg_context *ctx;

	ctx  = (struct liquidio_if_cfg_context *)sc->ctxptr;

	if (status) {
		dev_err(&oct->pci_dev->dev, "MTU change failed. Status: %llx\n",
			CVM_CAST64(status));
		WRITE_ONCE(ctx->cond, LIO_CHANGE_MTU_FAIL);
	} else {
		WRITE_ONCE(ctx->cond, LIO_CHANGE_MTU_SUCCESS);
	}

	/* This barrier is required to be sure that the response has been
	 * written fully before waking up the handler
	 */
	wmb();

	wake_up_interruptible(&ctx->wc);
}