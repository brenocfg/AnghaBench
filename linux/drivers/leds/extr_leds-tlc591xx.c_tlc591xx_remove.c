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
struct tlc591xx_priv {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLC591XX_MAX_LEDS ; 
 struct tlc591xx_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  tlc591xx_destroy_devices (struct tlc591xx_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tlc591xx_remove(struct i2c_client *client)
{
	struct tlc591xx_priv *priv = i2c_get_clientdata(client);

	tlc591xx_destroy_devices(priv, TLC591XX_MAX_LEDS);

	return 0;
}