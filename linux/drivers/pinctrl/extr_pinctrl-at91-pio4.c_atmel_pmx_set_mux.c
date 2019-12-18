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
typedef  unsigned int u32 ;
struct pinctrl_dev {int /*<<< orphan*/  dev; } ;
struct atmel_pioctrl {TYPE_1__* groups; } ;
struct TYPE_2__ {unsigned int name; unsigned int pin; } ;

/* Variables and functions */
 unsigned int ATMEL_PIO_CFGR_FUNC_MASK ; 
 unsigned int* atmel_functions ; 
 unsigned int atmel_pin_config_read (struct pinctrl_dev*,unsigned int) ; 
 int /*<<< orphan*/  atmel_pin_config_write (struct pinctrl_dev*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 struct atmel_pioctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int atmel_pmx_set_mux(struct pinctrl_dev *pctldev,
			     unsigned function,
			     unsigned group)
{
	struct atmel_pioctrl *atmel_pioctrl = pinctrl_dev_get_drvdata(pctldev);
	unsigned pin;
	u32 conf;

	dev_dbg(pctldev->dev, "enable function %s group %s\n",
		atmel_functions[function], atmel_pioctrl->groups[group].name);

	pin = atmel_pioctrl->groups[group].pin;
	conf = atmel_pin_config_read(pctldev, pin);
	conf &= (~ATMEL_PIO_CFGR_FUNC_MASK);
	conf |= (function & ATMEL_PIO_CFGR_FUNC_MASK);
	dev_dbg(pctldev->dev, "pin: %u, conf: 0x%08x\n", pin, conf);
	atmel_pin_config_write(pctldev, pin, conf);

	return 0;
}