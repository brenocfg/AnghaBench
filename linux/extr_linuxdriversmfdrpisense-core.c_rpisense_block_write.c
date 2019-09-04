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
struct rpisense {int /*<<< orphan*/  dev; int /*<<< orphan*/  i2c_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int i2c_master_send (int /*<<< orphan*/ ,char const*,int) ; 

int rpisense_block_write(struct rpisense *rpisense, const char *buf, int count)
{
	int ret = i2c_master_send(rpisense->i2c_client, buf, count);

	if (ret < 0)
		dev_err(rpisense->dev, "Block write failed\n");
	return ret;
}