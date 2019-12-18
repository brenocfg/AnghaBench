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
struct hisi_sas_device {scalar_t__ dev_type; struct domain_device* sas_device; } ;
struct hisi_hba {struct hisi_sas_device* devices; } ;
struct domain_device {int dummy; } ;

/* Variables and functions */
 int HISI_SAS_MAX_DEVICES ; 
 scalar_t__ SAS_PHY_UNUSED ; 
 int /*<<< orphan*/  hisi_sas_init_device (struct domain_device*) ; 

__attribute__((used)) static void hisi_sas_reset_init_all_devices(struct hisi_hba *hisi_hba)
{
	struct hisi_sas_device *sas_dev;
	struct domain_device *device;
	int i;

	for (i = 0; i < HISI_SAS_MAX_DEVICES; i++) {
		sas_dev = &hisi_hba->devices[i];
		device = sas_dev->sas_device;

		if ((sas_dev->dev_type == SAS_PHY_UNUSED) || !device)
			continue;

		hisi_sas_init_device(device);
	}
}