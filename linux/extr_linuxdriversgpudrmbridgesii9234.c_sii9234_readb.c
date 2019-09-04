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
struct sii9234 {int i2c_error; int /*<<< orphan*/  dev; struct i2c_client** client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_read_byte (struct i2c_client*) ; 
 int i2c_smbus_write_byte (struct i2c_client*,int) ; 
 int /*<<< orphan*/ * sii9234_client_name ; 

__attribute__((used)) static int sii9234_readb(struct sii9234 *ctx, int id, int offset)
{
	int ret;
	struct i2c_client *client = ctx->client[id];

	if (ctx->i2c_error)
		return ctx->i2c_error;

	ret = i2c_smbus_write_byte(client, offset);
	if (ret < 0) {
		dev_err(ctx->dev, "readb: %4s[0x%02x]\n",
			sii9234_client_name[id], offset);
		ctx->i2c_error = ret;
		return ret;
	}

	ret = i2c_smbus_read_byte(client);
	if (ret < 0) {
		dev_err(ctx->dev, "readb: %4s[0x%02x]\n",
			sii9234_client_name[id], offset);
		ctx->i2c_error = ret;
	}

	return ret;
}