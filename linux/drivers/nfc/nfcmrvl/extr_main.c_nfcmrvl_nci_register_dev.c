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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  reset_n_io; scalar_t__ hci_muxed; } ;
struct nfcmrvl_private {int phy; TYPE_1__ config; int /*<<< orphan*/  ndev; struct device* dev; struct nfcmrvl_if_ops* if_ops; void* drv_data; } ;
struct nfcmrvl_platform_data {int dummy; } ;
struct nfcmrvl_if_ops {int dummy; } ;
struct device {int dummy; } ;
typedef  enum nfcmrvl_phy { ____Placeholder_nfcmrvl_phy } nfcmrvl_phy ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ENOMEM ; 
 struct nfcmrvl_private* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int NCI_SPI_HDR_LEN ; 
 scalar_t__ NFCMRVL_HCI_EVENT_HEADER_SIZE ; 
 int NFCMRVL_PHY_SPI ; 
 int NFC_PROTO_FELICA_MASK ; 
 int NFC_PROTO_ISO14443_B_MASK ; 
 int NFC_PROTO_ISO14443_MASK ; 
 int NFC_PROTO_ISO15693_MASK ; 
 int NFC_PROTO_JEWEL_MASK ; 
 int NFC_PROTO_MIFARE_MASK ; 
 int NFC_PROTO_NFC_DEP_MASK ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int gpio_request_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct nfcmrvl_private*) ; 
 struct nfcmrvl_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct nfcmrvl_platform_data*,int) ; 
 int /*<<< orphan*/  nci_allocate_device (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  nci_free_device (int /*<<< orphan*/ ) ; 
 int nci_register_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_set_drvdata (int /*<<< orphan*/ ,struct nfcmrvl_private*) ; 
 int /*<<< orphan*/  nfc_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  nfc_info (struct device*,char*) ; 
 int /*<<< orphan*/  nfcmrvl_chip_halt (struct nfcmrvl_private*) ; 
 int /*<<< orphan*/  nfcmrvl_fw_dnld_deinit (struct nfcmrvl_private*) ; 
 int nfcmrvl_fw_dnld_init (struct nfcmrvl_private*) ; 
 int /*<<< orphan*/  nfcmrvl_nci_ops ; 

struct nfcmrvl_private *nfcmrvl_nci_register_dev(enum nfcmrvl_phy phy,
				void *drv_data,
				struct nfcmrvl_if_ops *ops,
				struct device *dev,
				struct nfcmrvl_platform_data *pdata)
{
	struct nfcmrvl_private *priv;
	int rc;
	int headroom;
	int tailroom;
	u32 protocols;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return ERR_PTR(-ENOMEM);

	priv->drv_data = drv_data;
	priv->if_ops = ops;
	priv->dev = dev;
	priv->phy = phy;

	memcpy(&priv->config, pdata, sizeof(*pdata));

	if (gpio_is_valid(priv->config.reset_n_io)) {
		rc = gpio_request_one(priv->config.reset_n_io,
				      GPIOF_OUT_INIT_LOW,
				      "nfcmrvl_reset_n");
		if (rc < 0) {
			priv->config.reset_n_io = -EINVAL;
			nfc_err(dev, "failed to request reset_n io\n");
		}
	}

	if (phy == NFCMRVL_PHY_SPI) {
		headroom = NCI_SPI_HDR_LEN;
		tailroom = 1;
	} else
		headroom = tailroom = 0;

	if (priv->config.hci_muxed)
		headroom += NFCMRVL_HCI_EVENT_HEADER_SIZE;

	protocols = NFC_PROTO_JEWEL_MASK
		| NFC_PROTO_MIFARE_MASK
		| NFC_PROTO_FELICA_MASK
		| NFC_PROTO_ISO14443_MASK
		| NFC_PROTO_ISO14443_B_MASK
		| NFC_PROTO_ISO15693_MASK
		| NFC_PROTO_NFC_DEP_MASK;

	priv->ndev = nci_allocate_device(&nfcmrvl_nci_ops, protocols,
					 headroom, tailroom);
	if (!priv->ndev) {
		nfc_err(dev, "nci_allocate_device failed\n");
		rc = -ENOMEM;
		goto error_free_gpio;
	}

	rc = nfcmrvl_fw_dnld_init(priv);
	if (rc) {
		nfc_err(dev, "failed to initialize FW download %d\n", rc);
		goto error_free_dev;
	}

	nci_set_drvdata(priv->ndev, priv);

	rc = nci_register_device(priv->ndev);
	if (rc) {
		nfc_err(dev, "nci_register_device failed %d\n", rc);
		goto error_fw_dnld_deinit;
	}

	/* Ensure that controller is powered off */
	nfcmrvl_chip_halt(priv);

	nfc_info(dev, "registered with nci successfully\n");
	return priv;

error_fw_dnld_deinit:
	nfcmrvl_fw_dnld_deinit(priv);
error_free_dev:
	nci_free_device(priv->ndev);
error_free_gpio:
	if (gpio_is_valid(priv->config.reset_n_io))
		gpio_free(priv->config.reset_n_io);
	kfree(priv);
	return ERR_PTR(rc);
}