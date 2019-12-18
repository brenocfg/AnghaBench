#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  sdio; } ;
struct brcmfmac_pd_device {int bus_type; scalar_t__ id; scalar_t__ rev; TYPE_2__ bus; int /*<<< orphan*/  country_codes; } ;
struct TYPE_7__ {int /*<<< orphan*/  txglomsz; } ;
struct TYPE_5__ {TYPE_3__ sdio; } ;
struct brcmf_mp_device {int p2p_enable; int roamoff; int iapp; int ignore_probe_fail; TYPE_1__ bus; int /*<<< orphan*/  country_codes; int /*<<< orphan*/  fcmode; int /*<<< orphan*/  feature_disable; } ;
typedef  enum brcmf_bus_type { ____Placeholder_brcmf_bus_type } brcmf_bus_type ;
struct TYPE_8__ {int device_count; struct brcmfmac_pd_device* devices; } ;

/* Variables and functions */
 int BRCMF_BUSTYPE_SDIO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  brcmf_dmi_probe (struct brcmf_mp_device*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_fcmode ; 
 int /*<<< orphan*/  brcmf_feature_disable ; 
 int /*<<< orphan*/  brcmf_iapp_enable ; 
 int /*<<< orphan*/  brcmf_ignore_probe_fail ; 
 int /*<<< orphan*/  brcmf_of_probe (struct device*,int,struct brcmf_mp_device*) ; 
 int /*<<< orphan*/  brcmf_p2p_enable ; 
 int /*<<< orphan*/  brcmf_roamoff ; 
 int /*<<< orphan*/  brcmf_sdiod_txglomsz ; 
 TYPE_4__* brcmfmac_pdata ; 
 struct brcmf_mp_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 

struct brcmf_mp_device *brcmf_get_module_param(struct device *dev,
					       enum brcmf_bus_type bus_type,
					       u32 chip, u32 chiprev)
{
	struct brcmf_mp_device *settings;
	struct brcmfmac_pd_device *device_pd;
	bool found;
	int i;

	brcmf_dbg(INFO, "Enter, bus=%d, chip=%d, rev=%d\n", bus_type, chip,
		  chiprev);
	settings = kzalloc(sizeof(*settings), GFP_ATOMIC);
	if (!settings)
		return NULL;

	/* start by using the module paramaters */
	settings->p2p_enable = !!brcmf_p2p_enable;
	settings->feature_disable = brcmf_feature_disable;
	settings->fcmode = brcmf_fcmode;
	settings->roamoff = !!brcmf_roamoff;
	settings->iapp = !!brcmf_iapp_enable;
#ifdef DEBUG
	settings->ignore_probe_fail = !!brcmf_ignore_probe_fail;
#endif

	if (bus_type == BRCMF_BUSTYPE_SDIO)
		settings->bus.sdio.txglomsz = brcmf_sdiod_txglomsz;

	/* See if there is any device specific platform data configured */
	found = false;
	if (brcmfmac_pdata) {
		for (i = 0; i < brcmfmac_pdata->device_count; i++) {
			device_pd = &brcmfmac_pdata->devices[i];
			if ((device_pd->bus_type == bus_type) &&
			    (device_pd->id == chip) &&
			    ((device_pd->rev == chiprev) ||
			     (device_pd->rev == -1))) {
				brcmf_dbg(INFO, "Platform data for device found\n");
				settings->country_codes =
						device_pd->country_codes;
				if (device_pd->bus_type == BRCMF_BUSTYPE_SDIO)
					memcpy(&settings->bus.sdio,
					       &device_pd->bus.sdio,
					       sizeof(settings->bus.sdio));
				found = true;
				break;
			}
		}
	}
	if (!found) {
		/* No platform data for this device, try OF and DMI data */
		brcmf_dmi_probe(settings, chip, chiprev);
		brcmf_of_probe(dev, bus_type, settings);
	}
	return settings;
}