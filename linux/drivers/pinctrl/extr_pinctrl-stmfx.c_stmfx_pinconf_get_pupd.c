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
typedef  int u32 ;
struct stmfx_pinctrl {TYPE_1__* stmfx; } ;
struct TYPE_2__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int STMFX_REG_GPIO_PUPD ; 
 int get_mask (unsigned int) ; 
 int get_reg (unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int stmfx_pinconf_get_pupd(struct stmfx_pinctrl *pctl,
				  unsigned int offset)
{
	u32 reg = STMFX_REG_GPIO_PUPD + get_reg(offset);
	u32 pupd, mask = get_mask(offset);
	int ret;

	ret = regmap_read(pctl->stmfx->map, reg, &pupd);
	if (ret)
		return ret;

	return !!(pupd & mask);
}