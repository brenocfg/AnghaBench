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
struct brcmf_pub {struct brcmf_proto* proto; TYPE_1__* bus_if; } ;
struct brcmf_proto {int /*<<< orphan*/ * debugfs_create; int /*<<< orphan*/ * add_tdls_peer; int /*<<< orphan*/ * delete_peer; int /*<<< orphan*/ * configure_addr_mode; int /*<<< orphan*/ * set_dcmd; int /*<<< orphan*/ * query_dcmd; int /*<<< orphan*/ * hdrpull; int /*<<< orphan*/  tx_queue_data; } ;
struct TYPE_2__ {scalar_t__ proto_type; } ;

/* Variables and functions */
 scalar_t__ BRCMF_PROTO_BCDC ; 
 scalar_t__ BRCMF_PROTO_MSGBUF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,...) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ brcmf_proto_bcdc_attach (struct brcmf_pub*) ; 
 scalar_t__ brcmf_proto_msgbuf_attach (struct brcmf_pub*) ; 
 int /*<<< orphan*/  kfree (struct brcmf_proto*) ; 
 struct brcmf_proto* kzalloc (int,int /*<<< orphan*/ ) ; 

int brcmf_proto_attach(struct brcmf_pub *drvr)
{
	struct brcmf_proto *proto;

	brcmf_dbg(TRACE, "Enter\n");

	proto = kzalloc(sizeof(*proto), GFP_ATOMIC);
	if (!proto)
		goto fail;

	drvr->proto = proto;

	if (drvr->bus_if->proto_type == BRCMF_PROTO_BCDC) {
		if (brcmf_proto_bcdc_attach(drvr))
			goto fail;
	} else if (drvr->bus_if->proto_type == BRCMF_PROTO_MSGBUF) {
		if (brcmf_proto_msgbuf_attach(drvr))
			goto fail;
	} else {
		bphy_err(drvr, "Unsupported proto type %d\n",
			 drvr->bus_if->proto_type);
		goto fail;
	}
	if (!proto->tx_queue_data || (proto->hdrpull == NULL) ||
	    (proto->query_dcmd == NULL) || (proto->set_dcmd == NULL) ||
	    (proto->configure_addr_mode == NULL) ||
	    (proto->delete_peer == NULL) || (proto->add_tdls_peer == NULL) ||
	    (proto->debugfs_create == NULL)) {
		bphy_err(drvr, "Not all proto handlers have been installed\n");
		goto fail;
	}
	return 0;

fail:
	kfree(proto);
	drvr->proto = NULL;
	return -ENOMEM;
}