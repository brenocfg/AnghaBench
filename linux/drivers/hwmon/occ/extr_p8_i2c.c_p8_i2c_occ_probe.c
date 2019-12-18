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
struct occ {int powr_sample_time_us; int poll_cmd_data; int /*<<< orphan*/  send_cmd; int /*<<< orphan*/ * bus_dev; } ;
struct p8_i2c_occ {struct occ occ; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct occ*) ; 
 struct p8_i2c_occ* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int occ_setup (struct occ*,char*) ; 
 int /*<<< orphan*/  p8_i2c_occ_send_cmd ; 

__attribute__((used)) static int p8_i2c_occ_probe(struct i2c_client *client,
			    const struct i2c_device_id *id)
{
	struct occ *occ;
	struct p8_i2c_occ *ctx = devm_kzalloc(&client->dev, sizeof(*ctx),
					      GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->client = client;
	occ = &ctx->occ;
	occ->bus_dev = &client->dev;
	dev_set_drvdata(&client->dev, occ);

	occ->powr_sample_time_us = 250;
	occ->poll_cmd_data = 0x10;		/* P8 OCC poll data */
	occ->send_cmd = p8_i2c_occ_send_cmd;

	return occ_setup(occ, "p8_occ");
}