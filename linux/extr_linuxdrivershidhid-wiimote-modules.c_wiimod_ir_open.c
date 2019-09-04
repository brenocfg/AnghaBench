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
struct wiimote_data {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIIPROTO_FLAG_IR_BASIC ; 
 struct wiimote_data* input_get_drvdata (struct input_dev*) ; 
 int wiimod_ir_change (struct wiimote_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wiimod_ir_open(struct input_dev *dev)
{
	struct wiimote_data *wdata = input_get_drvdata(dev);

	return wiimod_ir_change(wdata, WIIPROTO_FLAG_IR_BASIC);
}