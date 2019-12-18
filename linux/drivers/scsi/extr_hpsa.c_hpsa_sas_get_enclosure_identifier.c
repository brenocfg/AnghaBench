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
typedef  int /*<<< orphan*/  u64 ;
struct sas_rphy {int dummy; } ;
struct hpsa_scsi_dev_t {int /*<<< orphan*/  eli; } ;
struct ctlr_info {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 struct hpsa_scsi_dev_t* hpsa_find_device_by_sas_rphy (struct ctlr_info*,struct sas_rphy*) ; 
 struct Scsi_Host* phy_to_shost (struct sas_rphy*) ; 
 struct ctlr_info* shost_to_hba (struct Scsi_Host*) ; 

__attribute__((used)) static int
hpsa_sas_get_enclosure_identifier(struct sas_rphy *rphy, u64 *identifier)
{
	struct Scsi_Host *shost = phy_to_shost(rphy);
	struct ctlr_info *h;
	struct hpsa_scsi_dev_t *sd;

	if (!shost)
		return -ENXIO;

	h = shost_to_hba(shost);

	if (!h)
		return -ENXIO;

	sd = hpsa_find_device_by_sas_rphy(h, rphy);
	if (!sd)
		return -ENXIO;

	*identifier = sd->eli;

	return 0;
}