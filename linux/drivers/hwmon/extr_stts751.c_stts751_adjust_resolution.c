#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct stts751_priv {int interval; int res; int config; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int STTS751_CONF_RES_MASK ; 
 int STTS751_CONF_RES_SHIFT ; 
 int /*<<< orphan*/  STTS751_REG_CONF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int i2c_smbus_write_byte_data (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stts751_adjust_resolution(struct stts751_priv *priv)
{
	u8 res;

	switch (priv->interval) {
	case 9:
		/* 10 bits */
		res = 0;
		break;
	case 8:
		/* 11 bits */
		res = 1;
		break;
	default:
		/* 12 bits */
		res = 3;
		break;
	}

	if (priv->res == res)
		return 0;

	priv->config &= ~STTS751_CONF_RES_MASK;
	priv->config |= res << STTS751_CONF_RES_SHIFT;
	dev_dbg(&priv->client->dev, "setting res %d. config %x",
		res, priv->config);
	priv->res = res;

	return i2c_smbus_write_byte_data(priv->client,
				STTS751_REG_CONF, priv->config);
}