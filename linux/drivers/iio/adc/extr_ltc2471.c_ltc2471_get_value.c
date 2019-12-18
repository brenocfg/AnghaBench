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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EIO ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int i2c_master_recv (struct i2c_client*,char*,int) ; 

__attribute__((used)) static int ltc2471_get_value(struct i2c_client *client)
{
	int ret;
	__be16 buf;

	ret = i2c_master_recv(client, (char *)&buf, sizeof(buf));
	if (ret < 0)
		return ret;
	if (ret != sizeof(buf))
		return -EIO;

	/* MSB first */
	return be16_to_cpu(buf);
}