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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;
struct bttv {TYPE_1__ c; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_GPIO_DATA ; 
 int /*<<< orphan*/  BT848_GPIO_OUT_EN ; 
 int btread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btwrite (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
init_RTV24 (struct bttv *btv)
{
	uint32_t dataRead = 0;
	long watchdog_value = 0x0E;

	pr_info("%d: Adlink RTV-24 initialisation in progress ...\n",
		btv->c.nr);

	btwrite (0x00c3feff, BT848_GPIO_OUT_EN);

	btwrite (0 + watchdog_value, BT848_GPIO_DATA);
	msleep (1);
	btwrite (0x10 + watchdog_value, BT848_GPIO_DATA);
	msleep (10);
	btwrite (0 + watchdog_value, BT848_GPIO_DATA);

	dataRead = btread (BT848_GPIO_DATA);

	if ((((dataRead >> 18) & 0x01) != 0) || (((dataRead >> 19) & 0x01) != 1)) {
		pr_info("%d: Adlink RTV-24 initialisation(1) ERROR_CPLD_Check_Failed (read %d)\n",
			btv->c.nr, dataRead);
	}

	btwrite (0x4400 + watchdog_value, BT848_GPIO_DATA);
	msleep (10);
	btwrite (0x4410 + watchdog_value, BT848_GPIO_DATA);
	msleep (1);
	btwrite (watchdog_value, BT848_GPIO_DATA);
	msleep (1);
	dataRead = btread (BT848_GPIO_DATA);

	if ((((dataRead >> 18) & 0x01) != 0) || (((dataRead >> 19) & 0x01) != 0)) {
		pr_info("%d: Adlink RTV-24 initialisation(2) ERROR_CPLD_Check_Failed (read %d)\n",
			btv->c.nr, dataRead);

		return;
	}

	pr_info("%d: Adlink RTV-24 initialisation complete\n", btv->c.nr);
}