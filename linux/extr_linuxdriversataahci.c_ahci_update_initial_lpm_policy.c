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
struct ata_port {int target_lpm_policy; } ;
struct ahci_host_priv {int flags; } ;

/* Variables and functions */
 int AHCI_HFLAG_IS_MOBILE ; 
 int ATA_LPM_MIN_POWER ; 
 int ATA_LPM_UNKNOWN ; 
 int CONFIG_SATA_MOBILE_LPM_POLICY ; 
 int mobile_lpm_policy ; 

__attribute__((used)) static void ahci_update_initial_lpm_policy(struct ata_port *ap,
					   struct ahci_host_priv *hpriv)
{
	int policy = CONFIG_SATA_MOBILE_LPM_POLICY;


	/* Ignore processing for non mobile platforms */
	if (!(hpriv->flags & AHCI_HFLAG_IS_MOBILE))
		return;

	/* user modified policy via module param */
	if (mobile_lpm_policy != -1) {
		policy = mobile_lpm_policy;
		goto update_policy;
	}

#ifdef CONFIG_ACPI
	if (policy > ATA_LPM_MED_POWER &&
	    (acpi_gbl_FADT.flags & ACPI_FADT_LOW_POWER_S0)) {
		if (hpriv->cap & HOST_CAP_PART)
			policy = ATA_LPM_MIN_POWER_WITH_PARTIAL;
		else if (hpriv->cap & HOST_CAP_SSC)
			policy = ATA_LPM_MIN_POWER;
	}
#endif

update_policy:
	if (policy >= ATA_LPM_UNKNOWN && policy <= ATA_LPM_MIN_POWER)
		ap->target_lpm_policy = policy;
}