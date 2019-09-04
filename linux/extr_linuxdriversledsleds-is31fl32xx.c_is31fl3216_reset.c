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
struct is31fl32xx_priv {TYPE_1__* cdef; } ;
struct TYPE_2__ {unsigned int channels; scalar_t__ pwm_update_reg; scalar_t__ pwm_register_base; } ;

/* Variables and functions */
 scalar_t__ IS31FL3216_CHANNEL_CONFIG_REG ; 
 scalar_t__ IS31FL3216_CONFIG_REG ; 
 int IS31FL3216_CONFIG_SSD_ENABLE ; 
 scalar_t__ IS31FL3216_LIGHTING_EFFECT_REG ; 
 int is31fl32xx_write (struct is31fl32xx_priv*,scalar_t__,int) ; 

__attribute__((used)) static int is31fl3216_reset(struct is31fl32xx_priv *priv)
{
	unsigned int i;
	int ret;

	ret = is31fl32xx_write(priv, IS31FL3216_CONFIG_REG,
			       IS31FL3216_CONFIG_SSD_ENABLE);
	if (ret)
		return ret;
	for (i = 0; i < priv->cdef->channels; i++) {
		ret = is31fl32xx_write(priv, priv->cdef->pwm_register_base+i,
				       0x00);
		if (ret)
			return ret;
	}
	ret = is31fl32xx_write(priv, priv->cdef->pwm_update_reg, 0);
	if (ret)
		return ret;
	ret = is31fl32xx_write(priv, IS31FL3216_LIGHTING_EFFECT_REG, 0x00);
	if (ret)
		return ret;
	ret = is31fl32xx_write(priv, IS31FL3216_CHANNEL_CONFIG_REG, 0x00);
	if (ret)
		return ret;

	return 0;
}