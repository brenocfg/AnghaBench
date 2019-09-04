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
struct dvb_frontend {TYPE_1__* dvb; } ;
struct dvb_bt8xx_card {int /*<<< orphan*/  bttv_nr; } ;
struct TYPE_2__ {struct dvb_bt8xx_card* priv; } ;

/* Variables and functions */
 int bttv_gpio_enable (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bttv_write_gpio (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static void or51211_reset(struct dvb_frontend * fe)
{
	struct dvb_bt8xx_card *bt = fe->dvb->priv;

	/* RESET DEVICE
	 * reset is controlled by GPIO-0
	 * when set to 0 causes reset and when to 1 for normal op
	 * must remain reset for 128 clock cycles on a 50Mhz clock
	 * also PRM1 PRM2 & PRM4 are controlled by GPIO-1,GPIO-2 & GPIO-4
	 * We assume that the reset has be held low long enough or we
	 * have been reset by a power on.  When the driver is unloaded
	 * reset set to 0 so if reloaded we have been reset.
	 */
	/* reset & PRM1,2&4 are outputs */
	int ret = bttv_gpio_enable(bt->bttv_nr, 0x001F, 0x001F);
	if (ret != 0)
		pr_warn("or51211: Init Error - Can't Reset DVR (%i)\n", ret);
	bttv_write_gpio(bt->bttv_nr, 0x001F, 0x0000);   /* Reset */
	msleep(20);
	/* Now set for normal operation */
	bttv_write_gpio(bt->bttv_nr, 0x0001F, 0x0001);
	/* wait for operation to begin */
	msleep(500);
}