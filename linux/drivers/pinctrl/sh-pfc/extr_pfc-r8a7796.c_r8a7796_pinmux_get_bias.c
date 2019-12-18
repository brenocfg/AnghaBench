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
struct sh_pfc {int dummy; } ;
struct pinmux_bias_reg {int /*<<< orphan*/  pud; int /*<<< orphan*/  puen; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 unsigned int PIN_CONFIG_BIAS_DISABLE ; 
 unsigned int PIN_CONFIG_BIAS_PULL_DOWN ; 
 unsigned int PIN_CONFIG_BIAS_PULL_UP ; 
 struct pinmux_bias_reg* sh_pfc_pin_to_bias_reg (struct sh_pfc*,unsigned int,unsigned int*) ; 
 int sh_pfc_read (struct sh_pfc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int r8a7796_pinmux_get_bias(struct sh_pfc *pfc,
					    unsigned int pin)
{
	const struct pinmux_bias_reg *reg;
	unsigned int bit;

	reg = sh_pfc_pin_to_bias_reg(pfc, pin, &bit);
	if (!reg)
		return PIN_CONFIG_BIAS_DISABLE;

	if (!(sh_pfc_read(pfc, reg->puen) & BIT(bit)))
		return PIN_CONFIG_BIAS_DISABLE;
	else if (sh_pfc_read(pfc, reg->pud) & BIT(bit))
		return PIN_CONFIG_BIAS_PULL_UP;
	else
		return PIN_CONFIG_BIAS_PULL_DOWN;
}