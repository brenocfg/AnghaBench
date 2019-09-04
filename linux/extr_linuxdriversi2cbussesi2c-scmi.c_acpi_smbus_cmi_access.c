#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union i2c_smbus_data {int byte; int word; int* block; } ;
struct TYPE_7__ {int length; int /*<<< orphan*/  pointer; } ;
struct TYPE_6__ {int value; } ;
struct TYPE_5__ {union acpi_object* elements; } ;
union acpi_object {scalar_t__ type; TYPE_3__ buffer; TYPE_2__ integer; TYPE_1__ package; } ;
typedef  unsigned char u8 ;
typedef  unsigned char u16 ;
struct i2c_adapter {int /*<<< orphan*/  dev; struct acpi_smbus_cmi* algo_data; } ;
struct acpi_smbus_cmi {int /*<<< orphan*/  handle; TYPE_4__* methods; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_8__ {char* mt_sbr; char* mt_sbw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 unsigned char ACPI_SMBUS_PRTCL_BLOCK_DATA ; 
 unsigned char ACPI_SMBUS_PRTCL_BYTE ; 
 unsigned char ACPI_SMBUS_PRTCL_BYTE_DATA ; 
 unsigned char ACPI_SMBUS_PRTCL_QUICK ; 
 unsigned char ACPI_SMBUS_PRTCL_READ ; 
 unsigned char ACPI_SMBUS_PRTCL_WORD_DATA ; 
 unsigned char ACPI_SMBUS_PRTCL_WRITE ; 
#define  ACPI_SMBUS_STATUS_BUSY 136 
#define  ACPI_SMBUS_STATUS_DNAK 135 
#define  ACPI_SMBUS_STATUS_OK 134 
#define  ACPI_SMBUS_STATUS_TIMEOUT 133 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int EPROTO ; 
 int ETIMEDOUT ; 
#define  I2C_SMBUS_BLOCK_DATA 132 
 int I2C_SMBUS_BLOCK_MAX ; 
#define  I2C_SMBUS_BYTE 131 
#define  I2C_SMBUS_BYTE_DATA 130 
#define  I2C_SMBUS_QUICK 129 
 char I2C_SMBUS_READ ; 
#define  I2C_SMBUS_WORD_DATA 128 
 char I2C_SMBUS_WRITE ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,struct acpi_object_list*,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_handle_debug (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  acpi_handle_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
acpi_smbus_cmi_access(struct i2c_adapter *adap, u16 addr, unsigned short flags,
		   char read_write, u8 command, int size,
		   union i2c_smbus_data *data)
{
	int result = 0;
	struct acpi_smbus_cmi *smbus_cmi = adap->algo_data;
	unsigned char protocol;
	acpi_status status = 0;
	struct acpi_object_list input;
	union acpi_object mt_params[5];
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *obj;
	union acpi_object *pkg;
	char *method;
	int len = 0;

	dev_dbg(&adap->dev, "access size: %d %s\n", size,
		(read_write) ? "READ" : "WRITE");
	switch (size) {
	case I2C_SMBUS_QUICK:
		protocol = ACPI_SMBUS_PRTCL_QUICK;
		command = 0;
		if (read_write == I2C_SMBUS_WRITE) {
			mt_params[3].type = ACPI_TYPE_INTEGER;
			mt_params[3].integer.value = 0;
			mt_params[4].type = ACPI_TYPE_INTEGER;
			mt_params[4].integer.value = 0;
		}
		break;

	case I2C_SMBUS_BYTE:
		protocol = ACPI_SMBUS_PRTCL_BYTE;
		if (read_write == I2C_SMBUS_WRITE) {
			mt_params[3].type = ACPI_TYPE_INTEGER;
			mt_params[3].integer.value = 0;
			mt_params[4].type = ACPI_TYPE_INTEGER;
			mt_params[4].integer.value = 0;
		} else {
			command = 0;
		}
		break;

	case I2C_SMBUS_BYTE_DATA:
		protocol = ACPI_SMBUS_PRTCL_BYTE_DATA;
		if (read_write == I2C_SMBUS_WRITE) {
			mt_params[3].type = ACPI_TYPE_INTEGER;
			mt_params[3].integer.value = 1;
			mt_params[4].type = ACPI_TYPE_INTEGER;
			mt_params[4].integer.value = data->byte;
		}
		break;

	case I2C_SMBUS_WORD_DATA:
		protocol = ACPI_SMBUS_PRTCL_WORD_DATA;
		if (read_write == I2C_SMBUS_WRITE) {
			mt_params[3].type = ACPI_TYPE_INTEGER;
			mt_params[3].integer.value = 2;
			mt_params[4].type = ACPI_TYPE_INTEGER;
			mt_params[4].integer.value = data->word;
		}
		break;

	case I2C_SMBUS_BLOCK_DATA:
		protocol = ACPI_SMBUS_PRTCL_BLOCK_DATA;
		if (read_write == I2C_SMBUS_WRITE) {
			len = data->block[0];
			if (len == 0 || len > I2C_SMBUS_BLOCK_MAX)
				return -EINVAL;
			mt_params[3].type = ACPI_TYPE_INTEGER;
			mt_params[3].integer.value = len;
			mt_params[4].type = ACPI_TYPE_BUFFER;
			mt_params[4].buffer.length = len;
			mt_params[4].buffer.pointer = data->block + 1;
		}
		break;

	default:
		dev_warn(&adap->dev, "Unsupported transaction %d\n", size);
		return -EOPNOTSUPP;
	}

	if (read_write == I2C_SMBUS_READ) {
		protocol |= ACPI_SMBUS_PRTCL_READ;
		method = smbus_cmi->methods->mt_sbr;
		input.count = 3;
	} else {
		protocol |= ACPI_SMBUS_PRTCL_WRITE;
		method = smbus_cmi->methods->mt_sbw;
		input.count = 5;
	}

	input.pointer = mt_params;
	mt_params[0].type = ACPI_TYPE_INTEGER;
	mt_params[0].integer.value = protocol;
	mt_params[1].type = ACPI_TYPE_INTEGER;
	mt_params[1].integer.value = addr;
	mt_params[2].type = ACPI_TYPE_INTEGER;
	mt_params[2].integer.value = command;

	status = acpi_evaluate_object(smbus_cmi->handle, method, &input,
				      &buffer);
	if (ACPI_FAILURE(status)) {
		acpi_handle_err(smbus_cmi->handle,
				"Failed to evaluate %s: %i\n", method, status);
		return -EIO;
	}

	pkg = buffer.pointer;
	if (pkg && pkg->type == ACPI_TYPE_PACKAGE)
		obj = pkg->package.elements;
	else {
		acpi_handle_err(smbus_cmi->handle, "Invalid argument type\n");
		result = -EIO;
		goto out;
	}
	if (obj == NULL || obj->type != ACPI_TYPE_INTEGER) {
		acpi_handle_err(smbus_cmi->handle, "Invalid argument type\n");
		result = -EIO;
		goto out;
	}

	result = obj->integer.value;
	acpi_handle_debug(smbus_cmi->handle,  "%s return status: %i\n", method,
			  result);

	switch (result) {
	case ACPI_SMBUS_STATUS_OK:
		result = 0;
		break;
	case ACPI_SMBUS_STATUS_BUSY:
		result = -EBUSY;
		goto out;
	case ACPI_SMBUS_STATUS_TIMEOUT:
		result = -ETIMEDOUT;
		goto out;
	case ACPI_SMBUS_STATUS_DNAK:
		result = -ENXIO;
		goto out;
	default:
		result = -EIO;
		goto out;
	}

	if (read_write == I2C_SMBUS_WRITE || size == I2C_SMBUS_QUICK)
		goto out;

	obj = pkg->package.elements + 1;
	if (obj->type != ACPI_TYPE_INTEGER) {
		acpi_handle_err(smbus_cmi->handle, "Invalid argument type\n");
		result = -EIO;
		goto out;
	}

	len = obj->integer.value;
	obj = pkg->package.elements + 2;
	switch (size) {
	case I2C_SMBUS_BYTE:
	case I2C_SMBUS_BYTE_DATA:
	case I2C_SMBUS_WORD_DATA:
		if (obj->type != ACPI_TYPE_INTEGER) {
			acpi_handle_err(smbus_cmi->handle,
					"Invalid argument type\n");
			result = -EIO;
			goto out;
		}
		if (len == 2)
			data->word = obj->integer.value;
		else
			data->byte = obj->integer.value;
		break;
	case I2C_SMBUS_BLOCK_DATA:
		if (obj->type != ACPI_TYPE_BUFFER) {
			acpi_handle_err(smbus_cmi->handle,
					"Invalid argument type\n");
			result = -EIO;
			goto out;
		}
		if (len == 0 || len > I2C_SMBUS_BLOCK_MAX)
			return -EPROTO;
		data->block[0] = len;
		memcpy(data->block + 1, obj->buffer.pointer, len);
		break;
	}

out:
	kfree(buffer.pointer);
	dev_dbg(&adap->dev, "Transaction status: %i\n", result);
	return result;
}