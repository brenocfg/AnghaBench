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
typedef  int uint8_t ;
struct ht16k33_priv {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int REG_DISPLAY_SETUP ; 
 int REG_DISPLAY_SETUP_ON ; 
 int i2c_smbus_write_byte (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ht16k33_display_on(struct ht16k33_priv *priv)
{
	uint8_t data = REG_DISPLAY_SETUP | REG_DISPLAY_SETUP_ON;

	return i2c_smbus_write_byte(priv->client, data);
}