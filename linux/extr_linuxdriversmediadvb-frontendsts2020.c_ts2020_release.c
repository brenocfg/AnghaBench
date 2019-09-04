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
struct ts2020_priv {struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct ts2020_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 

__attribute__((used)) static void ts2020_release(struct dvb_frontend *fe)
{
	struct ts2020_priv *priv = fe->tuner_priv;
	struct i2c_client *client = priv->client;

	dev_dbg(&client->dev, "\n");

	i2c_unregister_device(client);
}