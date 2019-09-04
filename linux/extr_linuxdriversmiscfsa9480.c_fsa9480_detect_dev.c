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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct fsa9480_usbsw {int mansw; int dev1; int dev2; struct i2c_client* client; struct fsa9480_platform_data* pdata; } ;
struct fsa9480_platform_data {int /*<<< orphan*/  (* jig_cb ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* charger_cb ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* uart_cb ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* usb_cb ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int CON_INT_MASK ; 
 int CON_MANUAL_SW ; 
 int DEV_T1_CHARGER_MASK ; 
 int DEV_T1_UART_MASK ; 
 int DEV_T1_USB_MASK ; 
 int DEV_T2_JIG_MASK ; 
 int DEV_T2_UART_MASK ; 
 int DEV_T2_USB_MASK ; 
 int /*<<< orphan*/  FSA9480_ATTACHED ; 
 int /*<<< orphan*/  FSA9480_DETACHED ; 
 int /*<<< orphan*/  FSA9480_REG_CTRL ; 
 int /*<<< orphan*/  FSA9480_REG_DEV_T1 ; 
 int /*<<< orphan*/  FSA9480_REG_DEV_T2 ; 
 int /*<<< orphan*/  FSA9480_REG_MANSW1 ; 
 int INT_ATTACH ; 
 int INT_DETACH ; 
 int SW_UART ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int fsa9480_read_reg (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsa9480_write_reg (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsa9480_detect_dev(struct fsa9480_usbsw *usbsw, int intr)
{
	int val1, val2, ctrl;
	struct fsa9480_platform_data *pdata = usbsw->pdata;
	struct i2c_client *client = usbsw->client;

	val1 = fsa9480_read_reg(client, FSA9480_REG_DEV_T1);
	val2 = fsa9480_read_reg(client, FSA9480_REG_DEV_T2);
	ctrl = fsa9480_read_reg(client, FSA9480_REG_CTRL);

	dev_info(&client->dev, "intr: 0x%x, dev1: 0x%x, dev2: 0x%x\n",
			intr, val1, val2);

	if (!intr)
		goto out;

	if (intr & INT_ATTACH) {	/* Attached */
		/* USB */
		if (val1 & DEV_T1_USB_MASK || val2 & DEV_T2_USB_MASK) {
			if (pdata->usb_cb)
				pdata->usb_cb(FSA9480_ATTACHED);

			if (usbsw->mansw) {
				fsa9480_write_reg(client,
					FSA9480_REG_MANSW1, usbsw->mansw);
			}
		}

		/* UART */
		if (val1 & DEV_T1_UART_MASK || val2 & DEV_T2_UART_MASK) {
			if (pdata->uart_cb)
				pdata->uart_cb(FSA9480_ATTACHED);

			if (!(ctrl & CON_MANUAL_SW)) {
				fsa9480_write_reg(client,
					FSA9480_REG_MANSW1, SW_UART);
			}
		}

		/* CHARGER */
		if (val1 & DEV_T1_CHARGER_MASK) {
			if (pdata->charger_cb)
				pdata->charger_cb(FSA9480_ATTACHED);
		}

		/* JIG */
		if (val2 & DEV_T2_JIG_MASK) {
			if (pdata->jig_cb)
				pdata->jig_cb(FSA9480_ATTACHED);
		}
	} else if (intr & INT_DETACH) {	/* Detached */
		/* USB */
		if (usbsw->dev1 & DEV_T1_USB_MASK ||
			usbsw->dev2 & DEV_T2_USB_MASK) {
			if (pdata->usb_cb)
				pdata->usb_cb(FSA9480_DETACHED);
		}

		/* UART */
		if (usbsw->dev1 & DEV_T1_UART_MASK ||
			usbsw->dev2 & DEV_T2_UART_MASK) {
			if (pdata->uart_cb)
				pdata->uart_cb(FSA9480_DETACHED);
		}

		/* CHARGER */
		if (usbsw->dev1 & DEV_T1_CHARGER_MASK) {
			if (pdata->charger_cb)
				pdata->charger_cb(FSA9480_DETACHED);
		}

		/* JIG */
		if (usbsw->dev2 & DEV_T2_JIG_MASK) {
			if (pdata->jig_cb)
				pdata->jig_cb(FSA9480_DETACHED);
		}
	}

	usbsw->dev1 = val1;
	usbsw->dev2 = val2;

out:
	ctrl &= ~CON_INT_MASK;
	fsa9480_write_reg(client, FSA9480_REG_CTRL, ctrl);
}