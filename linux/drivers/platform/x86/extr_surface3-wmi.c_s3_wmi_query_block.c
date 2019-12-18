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
struct TYPE_4__ {int value; } ;
struct TYPE_3__ {int /*<<< orphan*/  length; } ;
union acpi_object {scalar_t__ type; TYPE_2__ integer; TYPE_1__ buffer; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int EINVAL ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3_wmi_lock ; 
 int /*<<< orphan*/  wmi_query_block (char const*,int,struct acpi_buffer*) ; 

__attribute__((used)) static int s3_wmi_query_block(const char *guid, int instance, int *ret)
{
	struct acpi_buffer output = { ACPI_ALLOCATE_BUFFER, NULL };
	acpi_status status;
	union acpi_object *obj;
	int error = 0;

	mutex_lock(&s3_wmi_lock);
	status = wmi_query_block(guid, instance, &output);

	obj = output.pointer;

	if (!obj || obj->type != ACPI_TYPE_INTEGER) {
		if (obj) {
			pr_err("query block returned object type: %d - buffer length:%d\n",
			       obj->type,
			       obj->type == ACPI_TYPE_BUFFER ?
						obj->buffer.length : 0);
		}
		error = -EINVAL;
		goto out_free_unlock;
	}
	*ret = obj->integer.value;
 out_free_unlock:
	kfree(obj);
	mutex_unlock(&s3_wmi_lock);
	return error;
}