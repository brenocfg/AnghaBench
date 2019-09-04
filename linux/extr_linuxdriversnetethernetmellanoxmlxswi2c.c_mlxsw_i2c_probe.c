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
typedef  scalar_t__ u8 ;
struct TYPE_4__ {int /*<<< orphan*/ * dev; int /*<<< orphan*/  device_name; int /*<<< orphan*/  device_kind; } ;
struct TYPE_3__ {int /*<<< orphan*/  mb_off_out; int /*<<< orphan*/  mb_size_out; int /*<<< orphan*/  mb_off_in; int /*<<< orphan*/  mb_size_in; int /*<<< orphan*/  lock; } ;
struct mlxsw_i2c {TYPE_2__ bus_info; int /*<<< orphan*/ * dev; TYPE_1__ cmd; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlxsw_i2c* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct mlxsw_i2c*) ; 
 int mlxsw_core_bus_device_register (TYPE_2__*,int /*<<< orphan*/ *,struct mlxsw_i2c*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_i2c_bus ; 
 int mlxsw_i2c_get_mbox (struct i2c_client*,struct mlxsw_i2c*) ; 
 int mlxsw_i2c_wait_go_bit (struct i2c_client*,struct mlxsw_i2c*,scalar_t__*) ; 
 int mlxsw_i2c_write_cmd (struct i2c_client*,struct mlxsw_i2c*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxsw_i2c_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	struct mlxsw_i2c *mlxsw_i2c;
	u8 status;
	int err;

	mlxsw_i2c = devm_kzalloc(&client->dev, sizeof(*mlxsw_i2c), GFP_KERNEL);
	if (!mlxsw_i2c)
		return -ENOMEM;

	i2c_set_clientdata(client, mlxsw_i2c);
	mutex_init(&mlxsw_i2c->cmd.lock);

	/* In order to use mailboxes through the i2c, special area is reserved
	 * on the i2c address space that can be used for input and output
	 * mailboxes. Such mailboxes are called local mailboxes. When using a
	 * local mailbox, software should specify 0 as the Input/Output
	 * parameters. The location of the Local Mailbox addresses on the i2c
	 * space can be retrieved through the QUERY_FW command.
	 * For this purpose QUERY_FW is to be issued with opcode modifier equal
	 * 0x01. For such command the output parameter is an immediate value.
	 * Here QUERY_FW command is invoked for ASIC probing and for getting
	 * local mailboxes addresses from immedate output parameters.
	 */

	/* Prepare and write out Command Interface Register for transaction */
	err = mlxsw_i2c_write_cmd(client, mlxsw_i2c, 1);
	if (err) {
		dev_err(&client->dev, "Could not start transaction");
		goto errout;
	}

	/* Wait until go bit is cleared. */
	err = mlxsw_i2c_wait_go_bit(client, mlxsw_i2c, &status);
	if (err) {
		dev_err(&client->dev, "HW semaphore is not released");
		goto errout;
	}

	/* Validate transaction completion status. */
	if (status) {
		dev_err(&client->dev, "Bad transaction completion status %x\n",
			status);
		err = -EIO;
		goto errout;
	}

	/* Get mailbox offsets. */
	err = mlxsw_i2c_get_mbox(client, mlxsw_i2c);
	if (err < 0) {
		dev_err(&client->dev, "Fail to get mailboxes\n");
		goto errout;
	}

	dev_info(&client->dev, "%s mb size=%x off=0x%08x out mb size=%x off=0x%08x\n",
		 id->name, mlxsw_i2c->cmd.mb_size_in,
		 mlxsw_i2c->cmd.mb_off_in, mlxsw_i2c->cmd.mb_size_out,
		 mlxsw_i2c->cmd.mb_off_out);

	/* Register device bus. */
	mlxsw_i2c->bus_info.device_kind = id->name;
	mlxsw_i2c->bus_info.device_name = client->name;
	mlxsw_i2c->bus_info.dev = &client->dev;
	mlxsw_i2c->dev = &client->dev;

	err = mlxsw_core_bus_device_register(&mlxsw_i2c->bus_info,
					     &mlxsw_i2c_bus, mlxsw_i2c, false,
					     NULL);
	if (err) {
		dev_err(&client->dev, "Fail to register core bus\n");
		return err;
	}

	return 0;

errout:
	i2c_set_clientdata(client, NULL);

	return err;
}