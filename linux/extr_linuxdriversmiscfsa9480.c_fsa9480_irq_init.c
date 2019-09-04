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
struct i2c_client {int /*<<< orphan*/  dev; scalar_t__ irq; } ;
struct fsa9480_usbsw {scalar_t__ mansw; struct i2c_client* client; struct fsa9480_platform_data* pdata; } ;
struct fsa9480_platform_data {int /*<<< orphan*/  wakeup; int /*<<< orphan*/  (* cfg_gpio ) () ;} ;

/* Variables and functions */
 unsigned int CON_MANUAL_SW ; 
 unsigned int CON_MASK ; 
 int /*<<< orphan*/  FSA9480_REG_CTRL ; 
 int /*<<< orphan*/  FSA9480_REG_INT1_MASK ; 
 int /*<<< orphan*/  FSA9480_REG_INT2_MASK ; 
 int /*<<< orphan*/  FSA9480_REG_MANSW1 ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsa9480_irq_handler ; 
 int /*<<< orphan*/  fsa9480_read_irq (struct i2c_client*,int*) ; 
 scalar_t__ fsa9480_read_reg (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsa9480_write_reg (struct i2c_client*,int /*<<< orphan*/ ,unsigned int) ; 
 int request_threaded_irq (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct fsa9480_usbsw*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int fsa9480_irq_init(struct fsa9480_usbsw *usbsw)
{
	struct fsa9480_platform_data *pdata = usbsw->pdata;
	struct i2c_client *client = usbsw->client;
	int ret;
	int intr;
	unsigned int ctrl = CON_MASK;

	/* clear interrupt */
	fsa9480_read_irq(client, &intr);

	/* unmask interrupt (attach/detach only) */
	fsa9480_write_reg(client, FSA9480_REG_INT1_MASK, 0xfc);
	fsa9480_write_reg(client, FSA9480_REG_INT2_MASK, 0x1f);

	usbsw->mansw = fsa9480_read_reg(client, FSA9480_REG_MANSW1);

	if (usbsw->mansw)
		ctrl &= ~CON_MANUAL_SW;	/* Manual Switching Mode */

	fsa9480_write_reg(client, FSA9480_REG_CTRL, ctrl);

	if (pdata && pdata->cfg_gpio)
		pdata->cfg_gpio();

	if (client->irq) {
		ret = request_threaded_irq(client->irq, NULL,
				fsa9480_irq_handler,
				IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				"fsa9480 micro USB", usbsw);
		if (ret) {
			dev_err(&client->dev, "failed to request IRQ\n");
			return ret;
		}

		if (pdata)
			device_init_wakeup(&client->dev, pdata->wakeup);
	}

	return 0;
}