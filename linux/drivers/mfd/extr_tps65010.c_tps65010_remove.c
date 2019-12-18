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
struct tps65010_board {int (* teardown ) (struct i2c_client*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  context; } ;
struct tps65010 {int /*<<< orphan*/  file; int /*<<< orphan*/  work; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int) ; 
 struct tps65010_board* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct tps65010*) ; 
 struct tps65010* i2c_get_clientdata (struct i2c_client*) ; 
 int stub1 (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * the_tps ; 

__attribute__((used)) static int tps65010_remove(struct i2c_client *client)
{
	struct tps65010		*tps = i2c_get_clientdata(client);
	struct tps65010_board	*board = dev_get_platdata(&client->dev);

	if (board && board->teardown) {
		int status = board->teardown(client, board->context);
		if (status < 0)
			dev_dbg(&client->dev, "board %s %s err %d\n",
				"teardown", client->name, status);
	}
	if (client->irq > 0)
		free_irq(client->irq, tps);
	cancel_delayed_work_sync(&tps->work);
	debugfs_remove(tps->file);
	the_tps = NULL;
	return 0;
}