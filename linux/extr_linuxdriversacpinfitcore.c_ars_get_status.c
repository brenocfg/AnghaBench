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
struct nvdimm_bus_descriptor {int (* ndctl ) (struct nvdimm_bus_descriptor*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nd_cmd_ars_status*,int /*<<< orphan*/ ,int*) ;} ;
struct nd_cmd_ars_status {int dummy; } ;
struct acpi_nfit_desc {int /*<<< orphan*/  max_ars; struct nd_cmd_ars_status* ars_status; struct nvdimm_bus_descriptor nd_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND_CMD_ARS_STATUS ; 
 int stub1 (struct nvdimm_bus_descriptor*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nd_cmd_ars_status*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ars_get_status(struct acpi_nfit_desc *acpi_desc)
{
	struct nvdimm_bus_descriptor *nd_desc = &acpi_desc->nd_desc;
	struct nd_cmd_ars_status *ars_status = acpi_desc->ars_status;
	int rc, cmd_rc;

	rc = nd_desc->ndctl(nd_desc, NULL, ND_CMD_ARS_STATUS, ars_status,
			acpi_desc->max_ars, &cmd_rc);
	if (rc < 0)
		return rc;
	return cmd_rc;
}