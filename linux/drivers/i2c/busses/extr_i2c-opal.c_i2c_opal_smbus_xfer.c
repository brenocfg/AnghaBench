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
union i2c_smbus_data {int byte; int word; int* block; } ;
typedef  int u8 ;
typedef  int u16 ;
struct opal_i2c_request {int subaddr_sz; void* type; void* subaddr; void* size; void* buffer_ra; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {scalar_t__ algo_data; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int EINVAL ; 
#define  I2C_SMBUS_BYTE 132 
#define  I2C_SMBUS_BYTE_DATA 131 
#define  I2C_SMBUS_I2C_BLOCK_DATA 130 
#define  I2C_SMBUS_QUICK 129 
 char I2C_SMBUS_READ ; 
#define  I2C_SMBUS_WORD_DATA 128 
 void* OPAL_I2C_RAW_READ ; 
 void* OPAL_I2C_RAW_WRITE ; 
 void* OPAL_I2C_SM_READ ; 
 void* OPAL_I2C_SM_WRITE ; 
 int /*<<< orphan*/  __pa (int*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int i2c_opal_send_request (unsigned long,struct opal_i2c_request*) ; 
 int /*<<< orphan*/  memset (struct opal_i2c_request*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i2c_opal_smbus_xfer(struct i2c_adapter *adap, u16 addr,
			       unsigned short flags, char read_write,
			       u8 command, int size, union i2c_smbus_data *data)
{
	unsigned long opal_id = (unsigned long)adap->algo_data;
	struct opal_i2c_request req;
	u8 local[2];
	int rc;

	memset(&req, 0, sizeof(req));

	req.addr = cpu_to_be16(addr);
	switch (size) {
	case I2C_SMBUS_BYTE:
		req.buffer_ra = cpu_to_be64(__pa(&data->byte));
		req.size = cpu_to_be32(1);
		/* Fall through */
	case I2C_SMBUS_QUICK:
		req.type = (read_write == I2C_SMBUS_READ) ?
			OPAL_I2C_RAW_READ : OPAL_I2C_RAW_WRITE;
		break;
	case I2C_SMBUS_BYTE_DATA:
		req.buffer_ra = cpu_to_be64(__pa(&data->byte));
		req.size = cpu_to_be32(1);
		req.subaddr = cpu_to_be32(command);
		req.subaddr_sz = 1;
		req.type = (read_write == I2C_SMBUS_READ) ?
			OPAL_I2C_SM_READ : OPAL_I2C_SM_WRITE;
		break;
	case I2C_SMBUS_WORD_DATA:
		if (!read_write) {
			local[0] = data->word & 0xff;
			local[1] = (data->word >> 8) & 0xff;
		}
		req.buffer_ra = cpu_to_be64(__pa(local));
		req.size = cpu_to_be32(2);
		req.subaddr = cpu_to_be32(command);
		req.subaddr_sz = 1;
		req.type = (read_write == I2C_SMBUS_READ) ?
			OPAL_I2C_SM_READ : OPAL_I2C_SM_WRITE;
		break;
	case I2C_SMBUS_I2C_BLOCK_DATA:
		req.buffer_ra = cpu_to_be64(__pa(&data->block[1]));
		req.size = cpu_to_be32(data->block[0]);
		req.subaddr = cpu_to_be32(command);
		req.subaddr_sz = 1;
		req.type = (read_write == I2C_SMBUS_READ) ?
			OPAL_I2C_SM_READ : OPAL_I2C_SM_WRITE;
		break;
	default:
		return -EINVAL;
	}

	rc = i2c_opal_send_request(opal_id, &req);
	if (!rc && read_write && size == I2C_SMBUS_WORD_DATA) {
		data->word = ((u16)local[1]) << 8;
		data->word |= local[0];
	}

	return rc;
}