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
struct nfcsim {int up; int rf_tech; int /*<<< orphan*/  mode; } ;
struct nfc_digital_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NFCSIM_ERR (struct nfcsim*,char*,int) ; 
 int /*<<< orphan*/  NFCSIM_MODE_INITIATOR ; 
#define  NFC_DIGITAL_CONFIG_FRAMING 129 
#define  NFC_DIGITAL_CONFIG_RF_TECH 128 
 struct nfcsim* nfc_digital_get_drvdata (struct nfc_digital_dev*) ; 

__attribute__((used)) static int nfcsim_in_configure_hw(struct nfc_digital_dev *ddev,
					  int type, int param)
{
	struct nfcsim *dev = nfc_digital_get_drvdata(ddev);

	switch (type) {
	case NFC_DIGITAL_CONFIG_RF_TECH:
		dev->up = true;
		dev->mode = NFCSIM_MODE_INITIATOR;
		dev->rf_tech = param;
		break;

	case NFC_DIGITAL_CONFIG_FRAMING:
		break;

	default:
		NFCSIM_ERR(dev, "Invalid configuration type: %d\n", type);
		return -EINVAL;
	}

	return 0;
}