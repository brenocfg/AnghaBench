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
typedef  enum sas_device_type { ____Placeholder_sas_device_type } sas_device_type ;

/* Variables and functions */
 int SAS_END_DEVICE ; 
 int SAS_SATA_PENDING ; 

__attribute__((used)) static bool dev_type_flutter(enum sas_device_type new, enum sas_device_type old)
{
	if (old == new)
		return true;

	/* treat device directed resets as flutter, if we went
	 * SAS_END_DEVICE to SAS_SATA_PENDING the link needs recovery
	 */
	if ((old == SAS_SATA_PENDING && new == SAS_END_DEVICE) ||
	    (old == SAS_END_DEVICE && new == SAS_SATA_PENDING))
		return true;

	return false;
}