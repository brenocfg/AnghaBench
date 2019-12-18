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
struct pm860x_touch {int /*<<< orphan*/  i2c; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEAS_EN3 ; 
 int MEAS_PD_EN ; 
 int MEAS_TSIX_EN ; 
 int MEAS_TSIY_EN ; 
 int MEAS_TSIZ1_EN ; 
 int MEAS_TSIZ2_EN ; 
 struct pm860x_touch* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  pm860x_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pm860x_touch_close(struct input_dev *dev)
{
	struct pm860x_touch *touch = input_get_drvdata(dev);
	int data;

	data = MEAS_PD_EN | MEAS_TSIX_EN | MEAS_TSIY_EN
		| MEAS_TSIZ1_EN | MEAS_TSIZ2_EN;
	pm860x_set_bits(touch->i2c, MEAS_EN3, data, 0);
}