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
struct TYPE_2__ {int /*<<< orphan*/  length; int /*<<< orphan*/  pointer; } ;
union acpi_object {scalar_t__ type; TYPE_1__ buffer; } ;
struct device {int /*<<< orphan*/  driver; } ;
struct acpi_nfit_desc {int dummy; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_nfit_desc_init (struct acpi_nfit_desc*,struct device*) ; 
 int acpi_nfit_init (struct acpi_nfit_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct acpi_nfit_desc* dev_get_drvdata (struct device*) ; 
 struct acpi_nfit_desc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  nfit_wq ; 

__attribute__((used)) static void acpi_nfit_update_notify(struct device *dev, acpi_handle handle)
{
	struct acpi_nfit_desc *acpi_desc = dev_get_drvdata(dev);
	struct acpi_buffer buf = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *obj;
	acpi_status status;
	int ret;

	if (!dev->driver) {
		/* dev->driver may be null if we're being removed */
		dev_dbg(dev, "no driver found for dev\n");
		return;
	}

	if (!acpi_desc) {
		acpi_desc = devm_kzalloc(dev, sizeof(*acpi_desc), GFP_KERNEL);
		if (!acpi_desc)
			return;
		acpi_nfit_desc_init(acpi_desc, dev);
	} else {
		/*
		 * Finish previous registration before considering new
		 * regions.
		 */
		flush_workqueue(nfit_wq);
	}

	/* Evaluate _FIT */
	status = acpi_evaluate_object(handle, "_FIT", NULL, &buf);
	if (ACPI_FAILURE(status)) {
		dev_err(dev, "failed to evaluate _FIT\n");
		return;
	}

	obj = buf.pointer;
	if (obj->type == ACPI_TYPE_BUFFER) {
		ret = acpi_nfit_init(acpi_desc, obj->buffer.pointer,
				obj->buffer.length);
		if (ret)
			dev_err(dev, "failed to merge updated NFIT\n");
	} else
		dev_err(dev, "Invalid _FIT\n");
	kfree(buf.pointer);
}