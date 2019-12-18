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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int mb_off_in; } ;
struct mlxsw_i2c {size_t block_size; TYPE_1__ cmd; } ;
struct i2c_msg {scalar_t__ len; int /*<<< orphan*/ * buf; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t MLXSW_I2C_ADDR_BUF_SIZE ; 
 scalar_t__ MLXSW_I2C_ADDR_WIDTH ; 
 int /*<<< orphan*/  MLXSW_I2C_PUSH_CMD_SIZE ; 
 int /*<<< orphan*/  MLXSW_I2C_RETRY ; 
 int /*<<< orphan*/  MLXSW_I2C_TIMEOUT_MSECS ; 
 struct i2c_msg MLXSW_I2C_WRITE_MSG (struct i2c_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct mlxsw_i2c* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlxsw_i2c_set_slave_addr (int /*<<< orphan*/ *,int) ; 
 int mlxsw_i2c_wait_go_bit (struct i2c_client*,struct mlxsw_i2c*,int /*<<< orphan*/ *) ; 
 int mlxsw_i2c_write_cmd (struct i2c_client*,struct mlxsw_i2c*,int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int
mlxsw_i2c_write(struct device *dev, size_t in_mbox_size, u8 *in_mbox, int num,
		u8 *p_status)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct mlxsw_i2c *mlxsw_i2c = i2c_get_clientdata(client);
	unsigned long timeout = msecs_to_jiffies(MLXSW_I2C_TIMEOUT_MSECS);
	int off = mlxsw_i2c->cmd.mb_off_in, chunk_size, i, j;
	unsigned long end;
	u8 *tran_buf;
	struct i2c_msg write_tran =
		MLXSW_I2C_WRITE_MSG(client, NULL, MLXSW_I2C_PUSH_CMD_SIZE);
	int err;

	tran_buf = kmalloc(mlxsw_i2c->block_size + MLXSW_I2C_ADDR_BUF_SIZE,
			   GFP_KERNEL);
	if (!tran_buf)
		return -ENOMEM;

	write_tran.buf = tran_buf;
	for (i = 0; i < num; i++) {
		chunk_size = (in_mbox_size > mlxsw_i2c->block_size) ?
			     mlxsw_i2c->block_size : in_mbox_size;
		write_tran.len = MLXSW_I2C_ADDR_WIDTH + chunk_size;
		mlxsw_i2c_set_slave_addr(tran_buf, off);
		memcpy(&tran_buf[MLXSW_I2C_ADDR_BUF_SIZE], in_mbox +
		       mlxsw_i2c->block_size * i, chunk_size);

		j = 0;
		end = jiffies + timeout;
		do {
			err = i2c_transfer(client->adapter, &write_tran, 1);
			if (err == 1)
				break;

			cond_resched();
		} while ((time_before(jiffies, end)) ||
			 (j++ < MLXSW_I2C_RETRY));

		if (err != 1) {
			if (!err) {
				err = -EIO;
				goto mlxsw_i2c_write_exit;
			}
		}

		off += chunk_size;
		in_mbox_size -= chunk_size;
	}

	/* Prepare and write out Command Interface Register for transaction. */
	err = mlxsw_i2c_write_cmd(client, mlxsw_i2c, 0);
	if (err) {
		dev_err(&client->dev, "Could not start transaction");
		err = -EIO;
		goto mlxsw_i2c_write_exit;
	}

	/* Wait until go bit is cleared. */
	err = mlxsw_i2c_wait_go_bit(client, mlxsw_i2c, p_status);
	if (err) {
		dev_err(&client->dev, "HW semaphore is not released");
		goto mlxsw_i2c_write_exit;
	}

	/* Validate transaction completion status. */
	if (*p_status) {
		dev_err(&client->dev, "Bad transaction completion status %x\n",
			*p_status);
		err = -EIO;
	}

mlxsw_i2c_write_exit:
	kfree(tran_buf);
	return err;
}