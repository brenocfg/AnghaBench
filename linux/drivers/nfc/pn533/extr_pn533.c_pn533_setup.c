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
typedef  int u8 ;
typedef  int /*<<< orphan*/  timing ;
struct pn533_config_timing {int /*<<< orphan*/  dep_timeout; void* atr_res_timeout; void* rfu; } ;
struct pn533_config_max_retries {int mx_rty_atr; int mx_rty_psl; int /*<<< orphan*/  mx_rty_passive_act; } ;
struct pn533 {int device_type; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  max_retries ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PN533_CFGITEM_MAX_RETRIES ; 
 int /*<<< orphan*/  PN533_CFGITEM_PASORI ; 
 int /*<<< orphan*/  PN533_CFGITEM_TIMING ; 
 int /*<<< orphan*/  PN533_CONFIG_MAX_RETRIES_NO_RETRY ; 
 void* PN533_CONFIG_TIMING_102 ; 
 int /*<<< orphan*/  PN533_CONFIG_TIMING_204 ; 
#define  PN533_DEVICE_ACR122U 131 
#define  PN533_DEVICE_PASORI 130 
#define  PN533_DEVICE_PN532 129 
#define  PN533_DEVICE_STD 128 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pn533_pasori_fw_reset (struct pn533*) ; 
 int pn533_set_configuration (struct pn533*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int pn533_setup(struct pn533 *dev)
{
	struct pn533_config_max_retries max_retries;
	struct pn533_config_timing timing;
	u8 pasori_cfg[3] = {0x08, 0x01, 0x08};
	int rc;

	switch (dev->device_type) {
	case PN533_DEVICE_STD:
	case PN533_DEVICE_PASORI:
	case PN533_DEVICE_ACR122U:
	case PN533_DEVICE_PN532:
		max_retries.mx_rty_atr = 0x2;
		max_retries.mx_rty_psl = 0x1;
		max_retries.mx_rty_passive_act =
			PN533_CONFIG_MAX_RETRIES_NO_RETRY;

		timing.rfu = PN533_CONFIG_TIMING_102;
		timing.atr_res_timeout = PN533_CONFIG_TIMING_102;
		timing.dep_timeout = PN533_CONFIG_TIMING_204;

		break;

	default:
		nfc_err(dev->dev, "Unknown device type %d\n",
			dev->device_type);
		return -EINVAL;
	}

	rc = pn533_set_configuration(dev, PN533_CFGITEM_MAX_RETRIES,
				     (u8 *)&max_retries, sizeof(max_retries));
	if (rc) {
		nfc_err(dev->dev,
			"Error on setting MAX_RETRIES config\n");
		return rc;
	}


	rc = pn533_set_configuration(dev, PN533_CFGITEM_TIMING,
				     (u8 *)&timing, sizeof(timing));
	if (rc) {
		nfc_err(dev->dev, "Error on setting RF timings\n");
		return rc;
	}

	switch (dev->device_type) {
	case PN533_DEVICE_STD:
	case PN533_DEVICE_PN532:
		break;

	case PN533_DEVICE_PASORI:
		pn533_pasori_fw_reset(dev);

		rc = pn533_set_configuration(dev, PN533_CFGITEM_PASORI,
					     pasori_cfg, 3);
		if (rc) {
			nfc_err(dev->dev,
				"Error while settings PASORI config\n");
			return rc;
		}

		pn533_pasori_fw_reset(dev);

		break;
	}

	return 0;
}