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
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int capability; int type; } ;

/* Variables and functions */
#define  ACER_AMW0 131 
#define  ACER_AMW0_V2 130 
 int ACER_CAP_BLUETOOTH ; 
 int ACER_CAP_MAILLED ; 
 int ACER_CAP_THREEG ; 
 int ACER_CAP_WIRELESS ; 
#define  ACER_WMID 129 
#define  ACER_WMID_v2 128 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AMW0_set_u32 (int,int) ; 
 int /*<<< orphan*/  WMID_GUID2 ; 
 int /*<<< orphan*/  WMID_set_u32 (int,int) ; 
 TYPE_1__* interface ; 
 int /*<<< orphan*/  wmi_has_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmid_v2_set_u32 (int,int) ; 

__attribute__((used)) static acpi_status set_u32(u32 value, u32 cap)
{
	acpi_status status;

	if (interface->capability & cap) {
		switch (interface->type) {
		case ACER_AMW0:
			return AMW0_set_u32(value, cap);
		case ACER_AMW0_V2:
			if (cap == ACER_CAP_MAILLED)
				return AMW0_set_u32(value, cap);

			/*
			 * On some models, some WMID methods don't toggle
			 * properly. For those cases, we want to run the AMW0
			 * method afterwards to be certain we've really toggled
			 * the device state.
			 */
			if (cap == ACER_CAP_WIRELESS ||
				cap == ACER_CAP_BLUETOOTH) {
				status = WMID_set_u32(value, cap);
				if (ACPI_FAILURE(status))
					return status;

				return AMW0_set_u32(value, cap);
			}
			/* fall through */
		case ACER_WMID:
			return WMID_set_u32(value, cap);
		case ACER_WMID_v2:
			if (cap & (ACER_CAP_WIRELESS |
				   ACER_CAP_BLUETOOTH |
				   ACER_CAP_THREEG))
				return wmid_v2_set_u32(value, cap);
			else if (wmi_has_guid(WMID_GUID2))
				return WMID_set_u32(value, cap);
			/* fall through */
		default:
			return AE_BAD_PARAMETER;
		}
	}
	return AE_BAD_PARAMETER;
}