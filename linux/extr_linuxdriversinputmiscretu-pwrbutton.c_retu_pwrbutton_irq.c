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
struct retu_dev {int dummy; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int /*<<< orphan*/  RETU_REG_STATUS ; 
 int RETU_STATUS_PWRONX ; 
 struct retu_dev* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int retu_read (struct retu_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t retu_pwrbutton_irq(int irq, void *_pwr)
{
	struct input_dev *idev = _pwr;
	struct retu_dev *rdev = input_get_drvdata(idev);
	bool state;

	state = !(retu_read(rdev, RETU_REG_STATUS) & RETU_STATUS_PWRONX);
	input_report_key(idev, KEY_POWER, state);
	input_sync(idev);

	return IRQ_HANDLED;
}