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
struct nfit_table_prev {int dummy; } ;
struct device {int dummy; } ;
struct acpi_nfit_header {int length; int type; } ;
struct acpi_nfit_desc {struct device* dev; } ;

/* Variables and functions */
#define  ACPI_NFIT_TYPE_CAPABILITIES 135 
#define  ACPI_NFIT_TYPE_CONTROL_REGION 134 
#define  ACPI_NFIT_TYPE_DATA_REGION 133 
#define  ACPI_NFIT_TYPE_FLUSH_ADDRESS 132 
#define  ACPI_NFIT_TYPE_INTERLEAVE 131 
#define  ACPI_NFIT_TYPE_MEMORY_MAP 130 
#define  ACPI_NFIT_TYPE_SMBIOS 129 
#define  ACPI_NFIT_TYPE_SYSTEM_ADDRESS 128 
 int /*<<< orphan*/  ENOMEM ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_bdw (struct acpi_nfit_desc*,struct nfit_table_prev*,void*) ; 
 int /*<<< orphan*/  add_dcr (struct acpi_nfit_desc*,struct nfit_table_prev*,void*) ; 
 int /*<<< orphan*/  add_flush (struct acpi_nfit_desc*,struct nfit_table_prev*,void*) ; 
 int /*<<< orphan*/  add_idt (struct acpi_nfit_desc*,struct nfit_table_prev*,void*) ; 
 int /*<<< orphan*/  add_memdev (struct acpi_nfit_desc*,struct nfit_table_prev*,void*) ; 
 int /*<<< orphan*/  add_platform_cap (struct acpi_nfit_desc*,void*) ; 
 int /*<<< orphan*/  add_spa (struct acpi_nfit_desc*,struct nfit_table_prev*,void*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 

__attribute__((used)) static void *add_table(struct acpi_nfit_desc *acpi_desc,
		struct nfit_table_prev *prev, void *table, const void *end)
{
	struct device *dev = acpi_desc->dev;
	struct acpi_nfit_header *hdr;
	void *err = ERR_PTR(-ENOMEM);

	if (table >= end)
		return NULL;

	hdr = table;
	if (!hdr->length) {
		dev_warn(dev, "found a zero length table '%d' parsing nfit\n",
			hdr->type);
		return NULL;
	}

	switch (hdr->type) {
	case ACPI_NFIT_TYPE_SYSTEM_ADDRESS:
		if (!add_spa(acpi_desc, prev, table))
			return err;
		break;
	case ACPI_NFIT_TYPE_MEMORY_MAP:
		if (!add_memdev(acpi_desc, prev, table))
			return err;
		break;
	case ACPI_NFIT_TYPE_CONTROL_REGION:
		if (!add_dcr(acpi_desc, prev, table))
			return err;
		break;
	case ACPI_NFIT_TYPE_DATA_REGION:
		if (!add_bdw(acpi_desc, prev, table))
			return err;
		break;
	case ACPI_NFIT_TYPE_INTERLEAVE:
		if (!add_idt(acpi_desc, prev, table))
			return err;
		break;
	case ACPI_NFIT_TYPE_FLUSH_ADDRESS:
		if (!add_flush(acpi_desc, prev, table))
			return err;
		break;
	case ACPI_NFIT_TYPE_SMBIOS:
		dev_dbg(dev, "smbios\n");
		break;
	case ACPI_NFIT_TYPE_CAPABILITIES:
		if (!add_platform_cap(acpi_desc, table))
			return err;
		break;
	default:
		dev_err(dev, "unknown table '%d' parsing nfit\n", hdr->type);
		break;
	}

	return table + hdr->length;
}