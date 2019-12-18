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
struct rc_dev {struct ir_rx51* priv; } ;
struct ir_rx51 {int /*<<< orphan*/  dev; int /*<<< orphan*/  pwm; int /*<<< orphan*/  device_is_open; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pwm_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ir_rx51_open(struct rc_dev *dev)
{
	struct ir_rx51 *ir_rx51 = dev->priv;

	if (test_and_set_bit(1, &ir_rx51->device_is_open))
		return -EBUSY;

	ir_rx51->pwm = pwm_get(ir_rx51->dev, NULL);
	if (IS_ERR(ir_rx51->pwm)) {
		int res = PTR_ERR(ir_rx51->pwm);

		dev_err(ir_rx51->dev, "pwm_get failed: %d\n", res);
		return res;
	}

	return 0;
}