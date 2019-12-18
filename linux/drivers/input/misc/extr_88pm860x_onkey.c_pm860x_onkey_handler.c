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
struct pm860x_onkey_info {int /*<<< orphan*/  i2c; int /*<<< orphan*/  idev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int /*<<< orphan*/  LONG_ONKEY_EN ; 
 int ONKEY_STATUS ; 
 int /*<<< orphan*/  PM8607_STATUS_2 ; 
 int /*<<< orphan*/  PM8607_WAKEUP ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int pm860x_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm860x_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t pm860x_onkey_handler(int irq, void *data)
{
	struct pm860x_onkey_info *info = data;
	int ret;

	ret = pm860x_reg_read(info->i2c, PM8607_STATUS_2);
	ret &= ONKEY_STATUS;
	input_report_key(info->idev, KEY_POWER, ret);
	input_sync(info->idev);

	/* Enable 8-second long onkey detection */
	pm860x_set_bits(info->i2c, PM8607_WAKEUP, 3, LONG_ONKEY_EN);
	return IRQ_HANDLED;
}