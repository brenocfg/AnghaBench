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
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ch7006_dbg (struct i2c_client*,char*) ; 
 int /*<<< orphan*/  ch7006_write (struct i2c_client*,int,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int ch7006_resume(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);

	ch7006_dbg(client, "\n");

	ch7006_write(client, 0x3d, 0x0);

	return 0;
}