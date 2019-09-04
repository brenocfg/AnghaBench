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
struct TYPE_2__ {union acpi_object* elements; } ;
union acpi_object {TYPE_1__ package; } ;
struct atk_data {int old_interface; } ;
typedef  enum atk_pack_member { ____Placeholder_atk_pack_member } atk_pack_member ;

/* Variables and functions */
#define  HWMON_PACK_ENABLE 132 
#define  HWMON_PACK_FLAGS 131 
#define  HWMON_PACK_LIMIT1 130 
#define  HWMON_PACK_LIMIT2 129 
#define  HWMON_PACK_NAME 128 
 int _HWMON_NEW_PACK_ENABLE ; 
 int _HWMON_NEW_PACK_FLAGS ; 
 int _HWMON_NEW_PACK_LIMIT1 ; 
 int _HWMON_NEW_PACK_LIMIT2 ; 
 int _HWMON_NEW_PACK_NAME ; 
 int _HWMON_OLD_PACK_ENABLE ; 
 int _HWMON_OLD_PACK_FLAGS ; 
 int _HWMON_OLD_PACK_LIMIT1 ; 
 int _HWMON_OLD_PACK_LIMIT2 ; 
 int _HWMON_OLD_PACK_NAME ; 

__attribute__((used)) static union acpi_object *atk_get_pack_member(struct atk_data *data,
						union acpi_object *pack,
						enum atk_pack_member m)
{
	bool old_if = data->old_interface;
	int offset;

	switch (m) {
	case HWMON_PACK_FLAGS:
		offset = old_if ? _HWMON_OLD_PACK_FLAGS : _HWMON_NEW_PACK_FLAGS;
		break;
	case HWMON_PACK_NAME:
		offset = old_if ? _HWMON_OLD_PACK_NAME : _HWMON_NEW_PACK_NAME;
		break;
	case HWMON_PACK_LIMIT1:
		offset = old_if ? _HWMON_OLD_PACK_LIMIT1 :
				  _HWMON_NEW_PACK_LIMIT1;
		break;
	case HWMON_PACK_LIMIT2:
		offset = old_if ? _HWMON_OLD_PACK_LIMIT2 :
				  _HWMON_NEW_PACK_LIMIT2;
		break;
	case HWMON_PACK_ENABLE:
		offset = old_if ? _HWMON_OLD_PACK_ENABLE :
				  _HWMON_NEW_PACK_ENABLE;
		break;
	default:
		return NULL;
	}

	return &pack->package.elements[offset];
}