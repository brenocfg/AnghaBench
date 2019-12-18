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
struct TYPE_4__ {int value; scalar_t__ type; } ;
struct TYPE_3__ {int count; union acpi_object* elements; } ;
union acpi_object {scalar_t__ type; TYPE_2__ integer; TYPE_1__ package; } ;
struct hns_mac_cb {int mac_id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int ENODEV ; 
 int /*<<< orphan*/  HNS_OP_GET_SFP_STAT_FUNC ; 
 union acpi_object* acpi_evaluate_dsm (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union acpi_object*) ; 
 int /*<<< orphan*/  hns_dsaf_acpi_dsm_guid ; 

__attribute__((used)) static int hns_mac_get_sfp_prsnt_acpi(struct hns_mac_cb *mac_cb, int *sfp_prsnt)
{
	union acpi_object *obj;
	union acpi_object obj_args, argv4;

	obj_args.integer.type = ACPI_TYPE_INTEGER;
	obj_args.integer.value = mac_cb->mac_id;

	argv4.type = ACPI_TYPE_PACKAGE,
	argv4.package.count = 1,
	argv4.package.elements = &obj_args,

	obj = acpi_evaluate_dsm(ACPI_HANDLE(mac_cb->dev),
				&hns_dsaf_acpi_dsm_guid, 0,
				HNS_OP_GET_SFP_STAT_FUNC, &argv4);

	if (!obj || obj->type != ACPI_TYPE_INTEGER)
		return -ENODEV;

	*sfp_prsnt = obj->integer.value;

	ACPI_FREE(obj);

	return 0;
}