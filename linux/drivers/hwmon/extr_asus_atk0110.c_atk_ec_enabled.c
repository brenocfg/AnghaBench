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
struct TYPE_3__ {scalar_t__ pointer; } ;
union acpi_object {TYPE_1__ buffer; } ;
struct device {int dummy; } ;
struct atk_data {TYPE_2__* acpi_dev; } ;
struct atk_acpi_ret_buffer {scalar_t__ flags; scalar_t__ value; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 int /*<<< orphan*/  ATK_EC_ID ; 
 int EIO ; 
 scalar_t__ IS_ERR (union acpi_object*) ; 
 int PTR_ERR (union acpi_object*) ; 
 union acpi_object* atk_gitm (struct atk_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 

__attribute__((used)) static int atk_ec_enabled(struct atk_data *data)
{
	struct device *dev = &data->acpi_dev->dev;
	union acpi_object *obj;
	struct atk_acpi_ret_buffer *buf;
	int err;

	obj = atk_gitm(data, ATK_EC_ID);
	if (IS_ERR(obj)) {
		dev_err(dev, "Unable to query EC status\n");
		return PTR_ERR(obj);
	}
	buf = (struct atk_acpi_ret_buffer *)obj->buffer.pointer;

	if (buf->flags == 0) {
		dev_err(dev, "Unable to query EC status\n");
		err = -EIO;
	} else {
		err = (buf->value != 0);
		dev_dbg(dev, "EC is %sabled\n",
				err ? "en" : "dis");
	}

	ACPI_FREE(obj);
	return err;
}