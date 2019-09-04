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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct cxd2820r_priv* demodulator_priv; } ;
struct cxd2820r_priv {int /*<<< orphan*/ * regmap; struct i2c_client** client; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ *,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int cxd2820r_i2c_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	struct cxd2820r_priv *priv = fe->demodulator_priv;
	struct i2c_client *client = priv->client[0];

	dev_dbg_ratelimited(&client->dev, "enable=%d\n", enable);

	return regmap_update_bits(priv->regmap[0], 0x00db, 0x01, enable ? 1 : 0);
}