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
struct device {int dummy; } ;
struct brcmf_pub {int /*<<< orphan*/  ops; scalar_t__ hdrlen; int /*<<< orphan*/  proto_block; int /*<<< orphan*/ * if2bss; } ;
struct brcmf_bus {struct brcmf_pub* drvr; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BRCMF_BSSIDX_INVALID ; 
 int /*<<< orphan*/  BRCMF_E_PSM_WATCHDOG ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,...) ; 
 int brcmf_bus_started (struct brcmf_pub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_detach (struct device*) ; 
 int /*<<< orphan*/  brcmf_fweh_attach (struct brcmf_pub*) ; 
 int /*<<< orphan*/  brcmf_fweh_register (struct brcmf_pub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int brcmf_proto_attach (struct brcmf_pub*) ; 
 int /*<<< orphan*/  brcmf_psm_watchdog_notify ; 
 struct brcmf_bus* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int brcmf_attach(struct device *dev)
{
	struct brcmf_bus *bus_if = dev_get_drvdata(dev);
	struct brcmf_pub *drvr = bus_if->drvr;
	int ret = 0;
	int i;

	brcmf_dbg(TRACE, "Enter\n");

	for (i = 0; i < ARRAY_SIZE(drvr->if2bss); i++)
		drvr->if2bss[i] = BRCMF_BSSIDX_INVALID;

	mutex_init(&drvr->proto_block);

	/* Link to bus module */
	drvr->hdrlen = 0;

	/* Attach and link in the protocol */
	ret = brcmf_proto_attach(drvr);
	if (ret != 0) {
		bphy_err(drvr, "brcmf_prot_attach failed\n");
		goto fail;
	}

	/* Attach to events important for core code */
	brcmf_fweh_register(drvr, BRCMF_E_PSM_WATCHDOG,
			    brcmf_psm_watchdog_notify);

	/* attach firmware event handler */
	brcmf_fweh_attach(drvr);

	ret = brcmf_bus_started(drvr, drvr->ops);
	if (ret != 0) {
		bphy_err(drvr, "dongle is not responding: err=%d\n", ret);
		goto fail;
	}

	return 0;

fail:
	brcmf_detach(dev);

	return ret;
}