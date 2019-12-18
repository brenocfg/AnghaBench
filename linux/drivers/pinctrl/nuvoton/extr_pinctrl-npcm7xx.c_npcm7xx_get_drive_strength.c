#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pinctrl_dev {int dummy; } ;
struct npcm7xx_pinctrl {struct npcm7xx_gpio* gpio_bank; } ;
struct TYPE_3__ {unsigned int ngpio; int /*<<< orphan*/  parent; } ;
struct npcm7xx_gpio {TYPE_1__ gc; scalar_t__ base; } ;
struct TYPE_4__ {int flag; } ;

/* Variables and functions */
 unsigned long BIT (int) ; 
 int DRIVE_STRENGTH_MASK ; 
 int DSHI (int) ; 
 int DSLO (int) ; 
 int EINVAL ; 
 unsigned int NPCM7XX_GPIO_PER_BANK ; 
 scalar_t__ NPCM7XX_GP_N_ODSC ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int,int) ; 
 unsigned long ioread32 (scalar_t__) ; 
 TYPE_2__* pincfg ; 
 struct npcm7xx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int npcm7xx_get_drive_strength(struct pinctrl_dev *pctldev,
				      unsigned int pin)
{
	struct npcm7xx_pinctrl *npcm = pinctrl_dev_get_drvdata(pctldev);
	struct npcm7xx_gpio *bank =
		&npcm->gpio_bank[pin / NPCM7XX_GPIO_PER_BANK];
	int gpio = (pin % bank->gc.ngpio);
	unsigned long pinmask = BIT(gpio);
	u32 ds = 0;
	int flg, val;

	flg = pincfg[pin].flag;
	if (flg & DRIVE_STRENGTH_MASK) {
		/* Get standard reading */
		val = ioread32(bank->base + NPCM7XX_GP_N_ODSC)
		& pinmask;
		ds = val ? DSHI(flg) : DSLO(flg);
		dev_dbg(bank->gc.parent,
			"pin %d strength %d = %d\n", pin, val, ds);
		return ds;
	}

	return -EINVAL;
}