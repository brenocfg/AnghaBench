#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* pointer; } ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
union acpi_object {TYPE_2__ string; TYPE_1__ integer; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct acpi_device_data {int dummy; } ;
typedef  enum dev_prop_type { ____Placeholder_dev_prop_type } dev_prop_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_TYPE_STRING ; 
 int DEV_PROP_STRING ; 
#define  DEV_PROP_U16 130 
#define  DEV_PROP_U32 129 
 int DEV_PROP_U64 ; 
#define  DEV_PROP_U8 128 
 int EINVAL ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  U16_MAX ; 
 int /*<<< orphan*/  U32_MAX ; 
 int /*<<< orphan*/  U8_MAX ; 
 int acpi_data_get_property (struct acpi_device_data const*,char const*,int /*<<< orphan*/ ,union acpi_object const**) ; 

__attribute__((used)) static int acpi_data_prop_read_single(const struct acpi_device_data *data,
				      const char *propname,
				      enum dev_prop_type proptype, void *val)
{
	const union acpi_object *obj;
	int ret;

	if (!val)
		return -EINVAL;

	if (proptype >= DEV_PROP_U8 && proptype <= DEV_PROP_U64) {
		ret = acpi_data_get_property(data, propname, ACPI_TYPE_INTEGER, &obj);
		if (ret)
			return ret;

		switch (proptype) {
		case DEV_PROP_U8:
			if (obj->integer.value > U8_MAX)
				return -EOVERFLOW;
			*(u8 *)val = obj->integer.value;
			break;
		case DEV_PROP_U16:
			if (obj->integer.value > U16_MAX)
				return -EOVERFLOW;
			*(u16 *)val = obj->integer.value;
			break;
		case DEV_PROP_U32:
			if (obj->integer.value > U32_MAX)
				return -EOVERFLOW;
			*(u32 *)val = obj->integer.value;
			break;
		default:
			*(u64 *)val = obj->integer.value;
			break;
		}
	} else if (proptype == DEV_PROP_STRING) {
		ret = acpi_data_get_property(data, propname, ACPI_TYPE_STRING, &obj);
		if (ret)
			return ret;

		*(char **)val = obj->string.pointer;

		return 1;
	} else {
		ret = -EINVAL;
	}
	return ret;
}