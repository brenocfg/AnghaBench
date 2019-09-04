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
struct i2c_client {int dummy; } ;
struct fsa9480_usbsw {struct i2c_client* client; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  fsa9480_detect_dev (struct fsa9480_usbsw*,int) ; 
 int /*<<< orphan*/  fsa9480_read_irq (struct i2c_client*,int*) ; 

__attribute__((used)) static irqreturn_t fsa9480_irq_handler(int irq, void *data)
{
	struct fsa9480_usbsw *usbsw = data;
	struct i2c_client *client = usbsw->client;
	int intr;

	/* clear interrupt */
	fsa9480_read_irq(client, &intr);

	/* device detection */
	fsa9480_detect_dev(usbsw, intr);

	return IRQ_HANDLED;
}