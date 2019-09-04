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
struct is31fl32xx_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS31FL3216_CONFIG_REG ; 
 int /*<<< orphan*/  IS31FL3216_CONFIG_SSD_DISABLE ; 
 int /*<<< orphan*/  IS31FL3216_CONFIG_SSD_ENABLE ; 
 int is31fl32xx_write (struct is31fl32xx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is31fl3216_software_shutdown(struct is31fl32xx_priv *priv,
					bool enable)
{
	u8 value = enable ? IS31FL3216_CONFIG_SSD_ENABLE :
			    IS31FL3216_CONFIG_SSD_DISABLE;

	return is31fl32xx_write(priv, IS31FL3216_CONFIG_REG, value);
}