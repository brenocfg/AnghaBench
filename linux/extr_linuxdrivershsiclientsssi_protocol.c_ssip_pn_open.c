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
struct ssi_protocol {int /*<<< orphan*/  lock; int /*<<< orphan*/  main_state; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct hsi_client {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  HANDSHAKE ; 
 int /*<<< orphan*/  SSIP_WAKETEST_FLAG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int hsi_claim_port (struct hsi_client*,int) ; 
 struct ssi_protocol* hsi_client_drvdata (struct hsi_client*) ; 
 int hsi_register_port_event (struct hsi_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsi_setup (struct hsi_client*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssi_waketest (struct hsi_client*,int) ; 
 int /*<<< orphan*/  ssip_port_event ; 
 int /*<<< orphan*/  ssip_send_bootinfo_req_cmd (struct hsi_client*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hsi_client* to_hsi_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssip_pn_open(struct net_device *dev)
{
	struct hsi_client *cl = to_hsi_client(dev->dev.parent);
	struct ssi_protocol *ssi = hsi_client_drvdata(cl);
	int err;

	err = hsi_claim_port(cl, 1);
	if (err < 0) {
		dev_err(&cl->device, "SSI port already claimed\n");
		return err;
	}
	err = hsi_register_port_event(cl, ssip_port_event);
	if (err < 0) {
		dev_err(&cl->device, "Register HSI port event failed (%d)\n",
			err);
		return err;
	}
	dev_dbg(&cl->device, "Configuring SSI port\n");
	hsi_setup(cl);

	if (!test_and_set_bit(SSIP_WAKETEST_FLAG, &ssi->flags))
		ssi_waketest(cl, 1); /* FIXME: To be removed */

	spin_lock_bh(&ssi->lock);
	ssi->main_state = HANDSHAKE;
	spin_unlock_bh(&ssi->lock);

	ssip_send_bootinfo_req_cmd(cl);

	return 0;
}