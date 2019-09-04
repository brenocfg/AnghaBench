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
typedef  int u16 ;
struct mcp3021_data {int sar_shift; int sar_mask; } ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EIO ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct mcp3021_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_master_recv (struct i2c_client*,char*,int) ; 

__attribute__((used)) static int mcp3021_read16(struct i2c_client *client)
{
	struct mcp3021_data *data = i2c_get_clientdata(client);
	int ret;
	u16 reg;
	__be16 buf;

	ret = i2c_master_recv(client, (char *)&buf, 2);
	if (ret < 0)
		return ret;
	if (ret != 2)
		return -EIO;

	/* The output code of the MCP3021 is transmitted with MSB first. */
	reg = be16_to_cpu(buf);

	/*
	 * The ten-bit output code is composed of the lower 4-bit of the
	 * first byte and the upper 6-bit of the second byte.
	 */
	reg = (reg >> data->sar_shift) & data->sar_mask;

	return reg;
}