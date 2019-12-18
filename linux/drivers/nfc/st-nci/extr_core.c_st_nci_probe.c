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
typedef  int u32 ;
struct st_nci_se_status {int dummy; } ;
struct st_nci_info {struct llt_ndlc* ndlc; } ;
struct llt_ndlc {int /*<<< orphan*/  ndev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NFC_PROTO_FELICA_MASK ; 
 int NFC_PROTO_ISO14443_B_MASK ; 
 int NFC_PROTO_ISO14443_MASK ; 
 int NFC_PROTO_ISO15693_MASK ; 
 int NFC_PROTO_JEWEL_MASK ; 
 int NFC_PROTO_MIFARE_MASK ; 
 int NFC_PROTO_NFC_DEP_MASK ; 
 struct st_nci_info* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_allocate_device (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  nci_free_device (int /*<<< orphan*/ ) ; 
 int nci_register_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_set_drvdata (int /*<<< orphan*/ ,struct st_nci_info*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  st_nci_ops ; 
 int st_nci_se_init (int /*<<< orphan*/ ,struct st_nci_se_status*) ; 
 int st_nci_vendor_cmds_init (int /*<<< orphan*/ ) ; 

int st_nci_probe(struct llt_ndlc *ndlc, int phy_headroom,
		 int phy_tailroom, struct st_nci_se_status *se_status)
{
	struct st_nci_info *info;
	int r;
	u32 protocols;

	info = devm_kzalloc(ndlc->dev,
			sizeof(struct st_nci_info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	protocols = NFC_PROTO_JEWEL_MASK
		| NFC_PROTO_MIFARE_MASK
		| NFC_PROTO_FELICA_MASK
		| NFC_PROTO_ISO14443_MASK
		| NFC_PROTO_ISO14443_B_MASK
		| NFC_PROTO_ISO15693_MASK
		| NFC_PROTO_NFC_DEP_MASK;

	ndlc->ndev = nci_allocate_device(&st_nci_ops, protocols,
					phy_headroom, phy_tailroom);
	if (!ndlc->ndev) {
		pr_err("Cannot allocate nfc ndev\n");
		return -ENOMEM;
	}
	info->ndlc = ndlc;

	nci_set_drvdata(ndlc->ndev, info);

	r = st_nci_vendor_cmds_init(ndlc->ndev);
	if (r) {
		pr_err("Cannot register proprietary vendor cmds\n");
		goto err_reg_dev;
	}

	r = nci_register_device(ndlc->ndev);
	if (r) {
		pr_err("Cannot register nfc device to nci core\n");
		goto err_reg_dev;
	}

	return st_nci_se_init(ndlc->ndev, se_status);

err_reg_dev:
	nci_free_device(ndlc->ndev);
	return r;
}