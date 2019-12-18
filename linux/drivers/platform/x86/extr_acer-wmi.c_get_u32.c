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
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  ACER_AMW0 131 
#define  ACER_AMW0_V2 130 
 int ACER_CAP_BLUETOOTH ; 
 int ACER_CAP_MAILLED ; 
 int ACER_CAP_THREEG ; 
 int ACER_CAP_WIRELESS ; 
#define  ACER_WMID 129 
#define  ACER_WMID_v2 128 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AMW0_get_u32 (int*,int) ; 
 int /*<<< orphan*/  WMID_GUID2 ; 
 int /*<<< orphan*/  WMID_get_u32 (int*,int) ; 
 TYPE_1__* interface ; 
 int /*<<< orphan*/  wmi_has_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmid_v2_get_u32 (int*,int) ; 

__attribute__((used)) static acpi_status get_u32(u32 *value, u32 cap)
{
	acpi_status status = AE_ERROR;

	switch (interface->type) {
	case ACER_AMW0:
		status = AMW0_get_u32(value, cap);
		break;
	case ACER_AMW0_V2:
		if (cap == ACER_CAP_MAILLED) {
			status = AMW0_get_u32(value, cap);
			break;
		}
		/* fall through */
	case ACER_WMID:
		status = WMID_get_u32(value, cap);
		break;
	case ACER_WMID_v2:
		if (cap & (ACER_CAP_WIRELESS |
			   ACER_CAP_BLUETOOTH |
			   ACER_CAP_THREEG))
			status = wmid_v2_get_u32(value, cap);
		else if (wmi_has_guid(WMID_GUID2))
			status = WMID_get_u32(value, cap);
		break;
	}

	return status;
}