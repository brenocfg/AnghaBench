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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int mailled; } ;

/* Variables and functions */
#define  ACER_CAP_BLUETOOTH 132 
#define  ACER_CAP_BRIGHTNESS 131 
#define  ACER_CAP_MAILLED 130 
#define  ACER_CAP_THREEG 129 
#define  ACER_CAP_WIRELESS 128 
 int ACER_WMID_GET_BLUETOOTH_METHODID ; 
 int ACER_WMID_GET_BRIGHTNESS_METHODID ; 
 int ACER_WMID_GET_THREEG_METHODID ; 
 int ACER_WMID_GET_WIRELESS_METHODID ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  WMI_execute_u32 (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ec_read (int,int*) ; 
 TYPE_1__* quirks ; 

__attribute__((used)) static acpi_status WMID_get_u32(u32 *value, u32 cap)
{
	acpi_status status;
	u8 tmp;
	u32 result, method_id = 0;

	switch (cap) {
	case ACER_CAP_WIRELESS:
		method_id = ACER_WMID_GET_WIRELESS_METHODID;
		break;
	case ACER_CAP_BLUETOOTH:
		method_id = ACER_WMID_GET_BLUETOOTH_METHODID;
		break;
	case ACER_CAP_BRIGHTNESS:
		method_id = ACER_WMID_GET_BRIGHTNESS_METHODID;
		break;
	case ACER_CAP_THREEG:
		method_id = ACER_WMID_GET_THREEG_METHODID;
		break;
	case ACER_CAP_MAILLED:
		if (quirks->mailled == 1) {
			ec_read(0x9f, &tmp);
			*value = tmp & 0x1;
			return 0;
		}
		/* fall through */
	default:
		return AE_ERROR;
	}
	status = WMI_execute_u32(method_id, 0, &result);

	if (ACPI_SUCCESS(status))
		*value = (u8)result;

	return status;
}