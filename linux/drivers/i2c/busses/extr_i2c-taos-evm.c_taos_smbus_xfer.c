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
union i2c_smbus_data {int byte; } ;
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct taos_data {char* buffer; scalar_t__ addr; int pos; scalar_t__ state; } ;
struct serio {int dummy; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; struct serio* algo_data; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int EPROTO ; 
#define  I2C_SMBUS_BYTE 129 
#define  I2C_SMBUS_BYTE_DATA 128 
 char I2C_SMBUS_WRITE ; 
 scalar_t__ TAOS_STATE_IDLE ; 
 scalar_t__ TAOS_STATE_RECV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ kstrtou8 (char*,int,int*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct taos_data* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  serio_write (struct serio*,char) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wq ; 

__attribute__((used)) static int taos_smbus_xfer(struct i2c_adapter *adapter, u16 addr,
			   unsigned short flags, char read_write, u8 command,
			   int size, union i2c_smbus_data *data)
{
	struct serio *serio = adapter->algo_data;
	struct taos_data *taos = serio_get_drvdata(serio);
	char *p;

	/* Encode our transaction. "@" is for the device address, "$" for the
	   SMBus command and "#" for the data. */
	p = taos->buffer;

	/* The device remembers the last used address, no need to send it
	   again if it's the same */
	if (addr != taos->addr)
		p += sprintf(p, "@%02X", addr);

	switch (size) {
	case I2C_SMBUS_BYTE:
		if (read_write == I2C_SMBUS_WRITE)
			sprintf(p, "$#%02X", command);
		else
			sprintf(p, "$");
		break;
	case I2C_SMBUS_BYTE_DATA:
		if (read_write == I2C_SMBUS_WRITE)
			sprintf(p, "$%02X#%02X", command, data->byte);
		else
			sprintf(p, "$%02X", command);
		break;
	default:
		dev_warn(&adapter->dev, "Unsupported transaction %d\n", size);
		return -EOPNOTSUPP;
	}

	/* Send the transaction to the TAOS EVM */
	dev_dbg(&adapter->dev, "Command buffer: %s\n", taos->buffer);
	for (p = taos->buffer; *p; p++)
		serio_write(serio, *p);

	taos->addr = addr;

	/* Start the transaction and read the answer */
	taos->pos = 0;
	taos->state = TAOS_STATE_RECV;
	serio_write(serio, read_write == I2C_SMBUS_WRITE ? '>' : '<');
	wait_event_interruptible_timeout(wq, taos->state == TAOS_STATE_IDLE,
					 msecs_to_jiffies(150));
	if (taos->state != TAOS_STATE_IDLE
	 || taos->pos != 5) {
		dev_err(&adapter->dev, "Transaction timeout (pos=%d)\n",
			taos->pos);
		return -EIO;
	}
	dev_dbg(&adapter->dev, "Answer buffer: %s\n", taos->buffer);

	/* Interpret the returned string */
	p = taos->buffer + 1;
	p[3] = '\0';
	if (!strcmp(p, "NAK"))
		return -ENODEV;

	if (read_write == I2C_SMBUS_WRITE) {
		if (!strcmp(p, "ACK"))
			return 0;
	} else {
		if (p[0] == 'x') {
			/*
			 * Voluntarily dropping error code of kstrtou8 since all
			 * error code that it could return are invalid according
			 * to Documentation/i2c/fault-codes.rst.
			 */
			if (kstrtou8(p + 1, 16, &data->byte))
				return -EPROTO;
			return 0;
		}
	}

	return -EIO;
}