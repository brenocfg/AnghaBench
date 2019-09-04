#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct lis3lv02d {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * mapped_btns; int /*<<< orphan*/  (* read ) (struct lis3lv02d*,int /*<<< orphan*/ ,int*) ;TYPE_1__* idev; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {struct input_dev* input; } ;

/* Variables and functions */
 int CLICK_SINGLE_X ; 
 int CLICK_SINGLE_Y ; 
 int CLICK_SINGLE_Z ; 
 int /*<<< orphan*/  CLICK_SRC ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct lis3lv02d*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void lis302dl_interrupt_handle_click(struct lis3lv02d *lis3)
{
	struct input_dev *dev = lis3->idev->input;
	u8 click_src;

	mutex_lock(&lis3->mutex);
	lis3->read(lis3, CLICK_SRC, &click_src);

	if (click_src & CLICK_SINGLE_X) {
		input_report_key(dev, lis3->mapped_btns[0], 1);
		input_report_key(dev, lis3->mapped_btns[0], 0);
	}

	if (click_src & CLICK_SINGLE_Y) {
		input_report_key(dev, lis3->mapped_btns[1], 1);
		input_report_key(dev, lis3->mapped_btns[1], 0);
	}

	if (click_src & CLICK_SINGLE_Z) {
		input_report_key(dev, lis3->mapped_btns[2], 1);
		input_report_key(dev, lis3->mapped_btns[2], 0);
	}
	input_sync(dev);
	mutex_unlock(&lis3->mutex);
}