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
struct sdhci_acpi_uid_slot {struct sdhci_acpi_slot const* slot; scalar_t__ uid; scalar_t__ hid; } ;
struct sdhci_acpi_slot {int dummy; } ;

/* Variables and functions */
 struct sdhci_acpi_uid_slot* sdhci_acpi_uids ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static const struct sdhci_acpi_slot *sdhci_acpi_get_slot(const char *hid,
							 const char *uid)
{
	const struct sdhci_acpi_uid_slot *u;

	for (u = sdhci_acpi_uids; u->hid; u++) {
		if (strcmp(u->hid, hid))
			continue;
		if (!u->uid)
			return u->slot;
		if (uid && !strcmp(u->uid, uid))
			return u->slot;
	}
	return NULL;
}