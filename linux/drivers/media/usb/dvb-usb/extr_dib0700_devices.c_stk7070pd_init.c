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
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO10 ; 
 int /*<<< orphan*/  GPIO4 ; 
 int /*<<< orphan*/  GPIO6 ; 
 int /*<<< orphan*/  GPIO7 ; 
 int /*<<< orphan*/  GPIO9 ; 
 int /*<<< orphan*/  GPIO_OUT ; 
 int /*<<< orphan*/  dib0700_ctrl_clock (struct dvb_usb_device*,int,int) ; 
 int /*<<< orphan*/  dib0700_set_gpio (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void stk7070pd_init(struct dvb_usb_device *dev)
{
	dib0700_set_gpio(dev, GPIO6, GPIO_OUT, 1);
	msleep(10);
	dib0700_set_gpio(dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctrl_clock(dev, 72, 1);

	msleep(10);
	dib0700_set_gpio(dev, GPIO10, GPIO_OUT, 1);
}