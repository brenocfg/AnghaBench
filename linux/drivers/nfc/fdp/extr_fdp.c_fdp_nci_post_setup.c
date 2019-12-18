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
struct nci_dev {int dummy; } ;
struct fdp_nci_info {int /*<<< orphan*/  clock_freq; int /*<<< orphan*/  clock_type; scalar_t__* fw_vsc_cfg; TYPE_1__* phy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;
struct TYPE_3__ {TYPE_2__* i2c_dev; } ;

/* Variables and functions */
 int fdp_nci_set_clock (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fdp_nci_set_production_data (struct nci_dev*,scalar_t__,scalar_t__*) ; 
 int nci_core_init (struct nci_dev*) ; 
 int nci_core_reset (struct nci_dev*) ; 
 struct fdp_nci_info* nci_get_drvdata (struct nci_dev*) ; 
 int /*<<< orphan*/  nfc_err (struct device*,char*,int) ; 

__attribute__((used)) static int fdp_nci_post_setup(struct nci_dev *ndev)
{
	struct fdp_nci_info *info = nci_get_drvdata(ndev);
	struct device *dev = &info->phy->i2c_dev->dev;
	int r;

	/* Check if the device has VSC */
	if (info->fw_vsc_cfg && info->fw_vsc_cfg[0]) {

		/* Set the vendor specific configuration */
		r = fdp_nci_set_production_data(ndev, info->fw_vsc_cfg[3],
						&info->fw_vsc_cfg[4]);
		if (r) {
			nfc_err(dev, "Vendor specific config set error %d\n",
				r);
			return r;
		}
	}

	/* Set clock type and frequency */
	r = fdp_nci_set_clock(ndev, info->clock_type, info->clock_freq);
	if (r) {
		nfc_err(dev, "Clock set error %d\n", r);
		return r;
	}

	/*
	 * In order to apply the VSC FDP needs a reset
	 */
	r = nci_core_reset(ndev);
	if (r)
		return r;

	/**
	 * The nci core was initialized when post setup was called
	 * so we leave it like that
	 */
	return nci_core_init(ndev);
}