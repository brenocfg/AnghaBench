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
struct max8925_onkey_info {int /*<<< orphan*/  i2c; int /*<<< orphan*/  dev; int /*<<< orphan*/  idev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HARDRESET_EN ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int /*<<< orphan*/  MAX8925_ON_OFF_STATUS ; 
 int /*<<< orphan*/  MAX8925_SYSENSEL ; 
 int SW_INPUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int max8925_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max8925_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t max8925_onkey_handler(int irq, void *data)
{
	struct max8925_onkey_info *info = data;
	int state;

	state = max8925_reg_read(info->i2c, MAX8925_ON_OFF_STATUS);

	input_report_key(info->idev, KEY_POWER, state & SW_INPUT);
	input_sync(info->idev);

	dev_dbg(info->dev, "onkey state:%d\n", state);

	/* Enable hardreset to halt if system isn't shutdown on time */
	max8925_set_bits(info->i2c, MAX8925_SYSENSEL,
			 HARDRESET_EN, HARDRESET_EN);

	return IRQ_HANDLED;
}