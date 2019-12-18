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
struct i2c_hid {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_HID_READ_PENDING ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  i2c_hid_get_input (struct i2c_hid*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t i2c_hid_irq(int irq, void *dev_id)
{
	struct i2c_hid *ihid = dev_id;

	if (test_bit(I2C_HID_READ_PENDING, &ihid->flags))
		return IRQ_HANDLED;

	i2c_hid_get_input(ihid);

	return IRQ_HANDLED;
}