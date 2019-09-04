#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct ht16k33_priv {TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_3__ {scalar_t__ irq; } ;

/* Variables and functions */
 int HT16K33_MATRIX_LED_MAX_COLS ; 
 int REG_ROWINT_SET ; 
 int REG_ROWINT_SET_INT_ACT_HIGH ; 
 int REG_ROWINT_SET_INT_EN ; 
 int REG_SYSTEM_SETUP ; 
 int REG_SYSTEM_SETUP_OSC_ON ; 
 int i2c_smbus_write_block_data (TYPE_1__*,int /*<<< orphan*/ ,int,int*) ; 
 int i2c_smbus_write_byte (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ht16k33_initialize(struct ht16k33_priv *priv)
{
	uint8_t byte;
	int err;
	uint8_t data[HT16K33_MATRIX_LED_MAX_COLS * 2];

	/* Clear RAM (8 * 16 bits) */
	memset(data, 0, sizeof(data));
	err = i2c_smbus_write_block_data(priv->client, 0, sizeof(data), data);
	if (err)
		return err;

	/* Turn on internal oscillator */
	byte = REG_SYSTEM_SETUP_OSC_ON | REG_SYSTEM_SETUP;
	err = i2c_smbus_write_byte(priv->client, byte);
	if (err)
		return err;

	/* Configure INT pin */
	byte = REG_ROWINT_SET | REG_ROWINT_SET_INT_ACT_HIGH;
	if (priv->client->irq > 0)
		byte |= REG_ROWINT_SET_INT_EN;
	return i2c_smbus_write_byte(priv->client, byte);
}