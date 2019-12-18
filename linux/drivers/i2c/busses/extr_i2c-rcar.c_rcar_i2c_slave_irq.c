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
typedef  int u8 ;
typedef  int u32 ;
struct rcar_i2c_priv {int /*<<< orphan*/  slave; } ;

/* Variables and functions */
 int FNA ; 
 int /*<<< orphan*/  I2C_SLAVE_READ_PROCESSED ; 
 int /*<<< orphan*/  I2C_SLAVE_READ_REQUESTED ; 
 int /*<<< orphan*/  I2C_SLAVE_STOP ; 
 int /*<<< orphan*/  I2C_SLAVE_WRITE_RECEIVED ; 
 int /*<<< orphan*/  I2C_SLAVE_WRITE_REQUESTED ; 
 int /*<<< orphan*/  ICRXTX ; 
 int /*<<< orphan*/  ICSCR ; 
 int /*<<< orphan*/  ICSIER ; 
 int /*<<< orphan*/  ICSSR ; 
 int SAR ; 
 int SDBS ; 
 int SDE ; 
 int SDR ; 
 int SIE ; 
 int SSR ; 
 int STM ; 
 int i2c_slave_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int rcar_i2c_read (struct rcar_i2c_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_i2c_write (struct rcar_i2c_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool rcar_i2c_slave_irq(struct rcar_i2c_priv *priv)
{
	u32 ssr_raw, ssr_filtered;
	u8 value;

	ssr_raw = rcar_i2c_read(priv, ICSSR) & 0xff;
	ssr_filtered = ssr_raw & rcar_i2c_read(priv, ICSIER);

	if (!ssr_filtered)
		return false;

	/* address detected */
	if (ssr_filtered & SAR) {
		/* read or write request */
		if (ssr_raw & STM) {
			i2c_slave_event(priv->slave, I2C_SLAVE_READ_REQUESTED, &value);
			rcar_i2c_write(priv, ICRXTX, value);
			rcar_i2c_write(priv, ICSIER, SDE | SSR | SAR);
		} else {
			i2c_slave_event(priv->slave, I2C_SLAVE_WRITE_REQUESTED, &value);
			rcar_i2c_read(priv, ICRXTX);	/* dummy read */
			rcar_i2c_write(priv, ICSIER, SDR | SSR | SAR);
		}

		rcar_i2c_write(priv, ICSSR, ~SAR & 0xff);
	}

	/* master sent stop */
	if (ssr_filtered & SSR) {
		i2c_slave_event(priv->slave, I2C_SLAVE_STOP, &value);
		rcar_i2c_write(priv, ICSIER, SAR | SSR);
		rcar_i2c_write(priv, ICSSR, ~SSR & 0xff);
	}

	/* master wants to write to us */
	if (ssr_filtered & SDR) {
		int ret;

		value = rcar_i2c_read(priv, ICRXTX);
		ret = i2c_slave_event(priv->slave, I2C_SLAVE_WRITE_RECEIVED, &value);
		/* Send NACK in case of error */
		rcar_i2c_write(priv, ICSCR, SIE | SDBS | (ret < 0 ? FNA : 0));
		rcar_i2c_write(priv, ICSSR, ~SDR & 0xff);
	}

	/* master wants to read from us */
	if (ssr_filtered & SDE) {
		i2c_slave_event(priv->slave, I2C_SLAVE_READ_PROCESSED, &value);
		rcar_i2c_write(priv, ICRXTX, value);
		rcar_i2c_write(priv, ICSSR, ~SDE & 0xff);
	}

	return true;
}