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
struct qeth_card {TYPE_1__* dev; } ;
struct diag26c_mac_resp {int resp_buf_len; scalar_t__ resp_version; scalar_t__ version; int* mac; int /*<<< orphan*/  devno; int /*<<< orphan*/  op_code; } ;
struct diag26c_mac_req {int resp_buf_len; scalar_t__ resp_version; scalar_t__ version; int* mac; int /*<<< orphan*/  devno; int /*<<< orphan*/  op_code; } ;
struct ccw_dev_id {int /*<<< orphan*/  devno; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DDEV (struct qeth_card*) ; 
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  DIAG26C_GET_MAC ; 
 int /*<<< orphan*/  DIAG26C_MAC_SERVICES ; 
 scalar_t__ DIAG26C_VERSION2 ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  QETH_CARD_HEX (struct qeth_card*,int,int*,int) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_HEX (int /*<<< orphan*/ ,int,struct diag26c_mac_resp*,int) ; 
 int /*<<< orphan*/  ccw_device_get_id (int /*<<< orphan*/ ,struct ccw_dev_id*) ; 
 int diag26c (struct diag26c_mac_resp*,struct diag26c_mac_resp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int*) ; 
 int /*<<< orphan*/  kfree (struct diag26c_mac_resp*) ; 
 struct diag26c_mac_resp* kzalloc (int,int) ; 

int qeth_vm_request_mac(struct qeth_card *card)
{
	struct diag26c_mac_resp *response;
	struct diag26c_mac_req *request;
	struct ccw_dev_id id;
	int rc;

	QETH_CARD_TEXT(card, 2, "vmreqmac");

	request = kzalloc(sizeof(*request), GFP_KERNEL | GFP_DMA);
	response = kzalloc(sizeof(*response), GFP_KERNEL | GFP_DMA);
	if (!request || !response) {
		rc = -ENOMEM;
		goto out;
	}

	ccw_device_get_id(CARD_DDEV(card), &id);
	request->resp_buf_len = sizeof(*response);
	request->resp_version = DIAG26C_VERSION2;
	request->op_code = DIAG26C_GET_MAC;
	request->devno = id.devno;

	QETH_DBF_HEX(CTRL, 2, request, sizeof(*request));
	rc = diag26c(request, response, DIAG26C_MAC_SERVICES);
	QETH_DBF_HEX(CTRL, 2, request, sizeof(*request));
	if (rc)
		goto out;
	QETH_DBF_HEX(CTRL, 2, response, sizeof(*response));

	if (request->resp_buf_len < sizeof(*response) ||
	    response->version != request->resp_version) {
		rc = -EIO;
		QETH_CARD_TEXT(card, 2, "badresp");
		QETH_CARD_HEX(card, 2, &request->resp_buf_len,
			      sizeof(request->resp_buf_len));
	} else if (!is_valid_ether_addr(response->mac)) {
		rc = -EINVAL;
		QETH_CARD_TEXT(card, 2, "badmac");
		QETH_CARD_HEX(card, 2, response->mac, ETH_ALEN);
	} else {
		ether_addr_copy(card->dev->dev_addr, response->mac);
	}

out:
	kfree(response);
	kfree(request);
	return rc;
}