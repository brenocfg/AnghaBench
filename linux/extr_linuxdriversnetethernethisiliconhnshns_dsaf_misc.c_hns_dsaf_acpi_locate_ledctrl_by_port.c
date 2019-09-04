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
struct TYPE_4__ {int count; union acpi_object* elements; } ;
struct TYPE_3__ {void* value; void* type; } ;
union acpi_object {TYPE_2__ package; int /*<<< orphan*/  type; TYPE_1__ integer; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct hns_mac_cb {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ ) ; 
 void* ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
 union acpi_object* acpi_evaluate_dsm (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union acpi_object*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,void*,void*) ; 
 int /*<<< orphan*/  hns_dsaf_acpi_dsm_guid ; 

__attribute__((used)) static void hns_dsaf_acpi_locate_ledctrl_by_port(struct hns_mac_cb *mac_cb,
						 u8 op_type, u32 locate,
						 u32 port)
{
	union acpi_object obj_args[2], argv4;
	union acpi_object *obj;

	obj_args[0].integer.type = ACPI_TYPE_INTEGER;
	obj_args[0].integer.value = locate;
	obj_args[1].integer.type = ACPI_TYPE_INTEGER;
	obj_args[1].integer.value = port;

	argv4.type = ACPI_TYPE_PACKAGE;
	argv4.package.count = 2;
	argv4.package.elements = obj_args;

	obj = acpi_evaluate_dsm(ACPI_HANDLE(mac_cb->dev),
				&hns_dsaf_acpi_dsm_guid, 0, op_type, &argv4);
	if (!obj) {
		dev_err(mac_cb->dev, "ledctrl fail, locate:%d port:%d!\n",
			locate, port);
		return;
	}

	ACPI_FREE(obj);
}