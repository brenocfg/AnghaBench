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
struct oct_mdio_cmd_context {int /*<<< orphan*/  wc; int /*<<< orphan*/  cond; int /*<<< orphan*/  octeon_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVM_CAST64 (scalar_t__) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct octeon_device* lio_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void octnet_mdio_resp_callback(struct octeon_device *oct,
				      u32 status,
				      void *buf)
{
	struct oct_mdio_cmd_context *mdio_cmd_ctx;
	struct octeon_soft_command *sc = (struct octeon_soft_command *)buf;

	mdio_cmd_ctx = (struct oct_mdio_cmd_context *)sc->ctxptr;

	oct = lio_get_device(mdio_cmd_ctx->octeon_id);
	if (status) {
		dev_err(&oct->pci_dev->dev, "MIDO instruction failed. Status: %llx\n",
			CVM_CAST64(status));
		WRITE_ONCE(mdio_cmd_ctx->cond, -1);
	} else {
		WRITE_ONCE(mdio_cmd_ctx->cond, 1);
	}
	wake_up_interruptible(&mdio_cmd_ctx->wc);
}