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
struct stts751_priv {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stts751_to_deg (int) ; 

__attribute__((used)) static int stts751_read_reg16(struct stts751_priv *priv, int *temp,
			      u8 hreg, u8 lreg)
{
	int integer, frac;

	integer = i2c_smbus_read_byte_data(priv->client, hreg);
	if (integer < 0)
		return integer;

	frac = i2c_smbus_read_byte_data(priv->client, lreg);
	if (frac < 0)
		return frac;

	*temp = stts751_to_deg((integer << 8) | frac);

	return 0;
}