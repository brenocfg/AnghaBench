#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct octeon_soft_command {scalar_t__ ctxptr; scalar_t__ virtrptr; } ;
struct TYPE_5__ {int /*<<< orphan*/  liquidio_firmware_version; } ;
struct octeon_device {TYPE_2__ fw_info; TYPE_1__* pci_dev; } ;
struct TYPE_6__ {char* liquidio_firmware_version; } ;
struct liquidio_if_cfg_resp {TYPE_3__ cfg_info; scalar_t__ status; } ;
struct liquidio_if_cfg_context {int /*<<< orphan*/  wc; int /*<<< orphan*/  cond; int /*<<< orphan*/  octeon_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVM_CAST64 (scalar_t__) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct octeon_device* lio_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

void lio_if_cfg_callback(struct octeon_device *oct,
			 u32 status __attribute__((unused)), void *buf)
{
	struct octeon_soft_command *sc = (struct octeon_soft_command *)buf;
	struct liquidio_if_cfg_context *ctx;
	struct liquidio_if_cfg_resp *resp;

	resp = (struct liquidio_if_cfg_resp *)sc->virtrptr;
	ctx = (struct liquidio_if_cfg_context *)sc->ctxptr;

	oct = lio_get_device(ctx->octeon_id);
	if (resp->status)
		dev_err(&oct->pci_dev->dev, "nic if cfg instruction failed. Status: %llx\n",
			CVM_CAST64(resp->status));
	WRITE_ONCE(ctx->cond, 1);

	snprintf(oct->fw_info.liquidio_firmware_version, 32, "%s",
		 resp->cfg_info.liquidio_firmware_version);

	/* This barrier is required to be sure that the response has been
	 * written fully before waking up the handler
	 */
	wmb();

	wake_up_interruptible(&ctx->wc);
}