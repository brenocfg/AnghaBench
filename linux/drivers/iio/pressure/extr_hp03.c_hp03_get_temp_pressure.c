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
typedef  int /*<<< orphan*/  u8 ;
struct hp03_priv {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  HP03_ADC_READ_REG ; 
 int /*<<< orphan*/  HP03_ADC_WRITE_REG ; 
 int i2c_smbus_read_word_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int hp03_get_temp_pressure(struct hp03_priv *priv, const u8 reg)
{
	int ret;

	ret = i2c_smbus_write_byte_data(priv->client, HP03_ADC_WRITE_REG, reg);
	if (ret < 0)
		return ret;

	msleep(50);	/* Wait for conversion to finish */

	return i2c_smbus_read_word_data(priv->client, HP03_ADC_READ_REG);
}