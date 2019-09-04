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

/* Variables and functions */
 int /*<<< orphan*/  RJ54N1_INIT_START ; 
 int /*<<< orphan*/  msleep (int) ; 
 int reg_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rj54n1_commit(struct i2c_client *client)
{
	int ret = reg_write(client, RJ54N1_INIT_START, 1);
	msleep(10);
	if (!ret)
		ret = reg_write(client, RJ54N1_INIT_START, 0);
	return ret;
}