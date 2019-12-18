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
struct isp1301 {int /*<<< orphan*/  work; int /*<<< orphan*/  timer; int /*<<< orphan*/  todo; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP1301_INTERRUPT_FALLING ; 
 int /*<<< orphan*/  ISP1301_INTERRUPT_RISING ; 
 int /*<<< orphan*/  WORK_STOP ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct isp1301*) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 struct isp1301* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  isp1301_clear_bits (struct isp1301*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ machine_is_omap_h2 () ; 
 int /*<<< orphan*/  otg_unbind (struct isp1301*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * the_transceiver ; 

__attribute__((used)) static int isp1301_remove(struct i2c_client *i2c)
{
	struct isp1301	*isp;

	isp = i2c_get_clientdata(i2c);

	isp1301_clear_bits(isp, ISP1301_INTERRUPT_FALLING, ~0);
	isp1301_clear_bits(isp, ISP1301_INTERRUPT_RISING, ~0);
	free_irq(i2c->irq, isp);
#ifdef	CONFIG_USB_OTG
	otg_unbind(isp);
#endif
	if (machine_is_omap_h2())
		gpio_free(2);

	set_bit(WORK_STOP, &isp->todo);
	del_timer_sync(&isp->timer);
	flush_work(&isp->work);

	put_device(&i2c->dev);
	the_transceiver = NULL;

	return 0;
}