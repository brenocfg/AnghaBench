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
struct sp2 {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct sp2* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct sp2*) ; 
 int /*<<< orphan*/  sp2_exit (struct i2c_client*) ; 

__attribute__((used)) static int sp2_remove(struct i2c_client *client)
{
	struct sp2 *s = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");
	sp2_exit(client);
	kfree(s);
	return 0;
}