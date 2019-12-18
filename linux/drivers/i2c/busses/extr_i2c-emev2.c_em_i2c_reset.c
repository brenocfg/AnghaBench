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
struct i2c_adapter {int dummy; } ;
struct em_i2c_device {scalar_t__ base; } ;

/* Variables and functions */
 int I2C_BIT_DFC0 ; 
 int I2C_BIT_IICE0 ; 
 int I2C_BIT_IICRSV ; 
 int I2C_BIT_STCEN ; 
 int I2C_BIT_WTIM0 ; 
 scalar_t__ I2C_OFS_IICACT0 ; 
 scalar_t__ I2C_OFS_IICC0 ; 
 scalar_t__ I2C_OFS_IICCL0 ; 
 scalar_t__ I2C_OFS_IICF0 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct em_i2c_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void em_i2c_reset(struct i2c_adapter *adap)
{
	struct em_i2c_device *priv = i2c_get_adapdata(adap);
	int retr;

	/* If I2C active */
	if (readb(priv->base + I2C_OFS_IICACT0) & I2C_BIT_IICE0) {
		/* Disable I2C operation */
		writeb(0, priv->base + I2C_OFS_IICACT0);

		retr = 1000;
		while (readb(priv->base + I2C_OFS_IICACT0) == 1 && retr)
			retr--;
		WARN_ON(retr == 0);
	}

	/* Transfer mode set */
	writeb(I2C_BIT_DFC0, priv->base + I2C_OFS_IICCL0);

	/* Can Issue start without detecting a stop, Reservation disabled. */
	writeb(I2C_BIT_STCEN | I2C_BIT_IICRSV, priv->base + I2C_OFS_IICF0);

	/* I2C enable, 9 bit interrupt mode */
	writeb(I2C_BIT_WTIM0, priv->base + I2C_OFS_IICC0);

	/* Enable I2C operation */
	writeb(I2C_BIT_IICE0, priv->base + I2C_OFS_IICACT0);

	retr = 1000;
	while (readb(priv->base + I2C_OFS_IICACT0) == 0 && retr)
		retr--;
	WARN_ON(retr == 0);
}