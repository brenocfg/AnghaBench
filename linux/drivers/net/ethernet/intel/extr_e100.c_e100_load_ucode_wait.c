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
struct nic {int /*<<< orphan*/  netdev; TYPE_2__* csr; int /*<<< orphan*/  cuc_cmd; struct cb* cb_to_clean; } ;
struct firmware {int dummy; } ;
struct cb {int status; } ;
struct TYPE_3__ {int /*<<< orphan*/  stat_ack; } ;
struct TYPE_4__ {TYPE_1__ scb; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ IS_ERR_OR_NULL (struct firmware const*) ; 
 int PTR_ERR_OR_ZERO (struct firmware const*) ; 
 int /*<<< orphan*/  cb_complete ; 
 int /*<<< orphan*/  cb_ok ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuc_start ; 
 int e100_exec_cb (struct nic*,void*,int /*<<< orphan*/ ) ; 
 struct firmware* e100_request_firmware (struct nic*) ; 
 int /*<<< orphan*/  e100_setup_ucode ; 
 int /*<<< orphan*/  e100_write_flush (struct nic*) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netif_err (struct nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline int e100_load_ucode_wait(struct nic *nic)
{
	const struct firmware *fw;
	int err = 0, counter = 50;
	struct cb *cb = nic->cb_to_clean;

	fw = e100_request_firmware(nic);
	/* If it's NULL, then no ucode is required */
	if (IS_ERR_OR_NULL(fw))
		return PTR_ERR_OR_ZERO(fw);

	if ((err = e100_exec_cb(nic, (void *)fw, e100_setup_ucode)))
		netif_err(nic, probe, nic->netdev,
			  "ucode cmd failed with error %d\n", err);

	/* must restart cuc */
	nic->cuc_cmd = cuc_start;

	/* wait for completion */
	e100_write_flush(nic);
	udelay(10);

	/* wait for possibly (ouch) 500ms */
	while (!(cb->status & cpu_to_le16(cb_complete))) {
		msleep(10);
		if (!--counter) break;
	}

	/* ack any interrupts, something could have been set */
	iowrite8(~0, &nic->csr->scb.stat_ack);

	/* if the command failed, or is not OK, notify and return */
	if (!counter || !(cb->status & cpu_to_le16(cb_ok))) {
		netif_err(nic, probe, nic->netdev, "ucode load failed\n");
		err = -EPERM;
	}

	return err;
}