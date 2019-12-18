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
struct is31fl32xx_priv {struct is31fl32xx_chipdef* cdef; } ;
struct is31fl32xx_chipdef {scalar_t__ led_control_register_base; int enable_bits_per_led_control_register; int channels; scalar_t__ global_control_reg; } ;

/* Variables and functions */
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 scalar_t__ IS31FL32XX_REG_NONE ; 
 int is31fl32xx_reset_regs (struct is31fl32xx_priv*) ; 
 int is31fl32xx_software_shutdown (struct is31fl32xx_priv*,int) ; 
 int is31fl32xx_write (struct is31fl32xx_priv*,scalar_t__,int) ; 

__attribute__((used)) static int is31fl32xx_init_regs(struct is31fl32xx_priv *priv)
{
	const struct is31fl32xx_chipdef *cdef = priv->cdef;
	int ret;

	ret = is31fl32xx_reset_regs(priv);
	if (ret)
		return ret;

	/*
	 * Set enable bit for all channels.
	 * We will control state with PWM registers alone.
	 */
	if (cdef->led_control_register_base != IS31FL32XX_REG_NONE) {
		u8 value =
		    GENMASK(cdef->enable_bits_per_led_control_register-1, 0);
		u8 num_regs = cdef->channels /
				cdef->enable_bits_per_led_control_register;
		int i;

		for (i = 0; i < num_regs; i++) {
			ret = is31fl32xx_write(priv,
					       cdef->led_control_register_base+i,
					       value);
			if (ret)
				return ret;
		}
	}

	ret = is31fl32xx_software_shutdown(priv, false);
	if (ret)
		return ret;

	if (cdef->global_control_reg != IS31FL32XX_REG_NONE) {
		ret = is31fl32xx_write(priv, cdef->global_control_reg, 0x00);
		if (ret)
			return ret;
	}

	return 0;
}