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
struct input_dev {int dummy; } ;
struct hampshire {scalar_t__ idx; int /*<<< orphan*/  data; struct input_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 scalar_t__ HAMPSHIRE_FORMAT_LENGTH ; 
 int /*<<< orphan*/  HAMPSHIRE_GET_TOUCHED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAMPSHIRE_GET_XC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAMPSHIRE_GET_YC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void hampshire_process_data(struct hampshire *phampshire)
{
	struct input_dev *dev = phampshire->dev;

	if (HAMPSHIRE_FORMAT_LENGTH == ++phampshire->idx) {
		input_report_abs(dev, ABS_X, HAMPSHIRE_GET_XC(phampshire->data));
		input_report_abs(dev, ABS_Y, HAMPSHIRE_GET_YC(phampshire->data));
		input_report_key(dev, BTN_TOUCH,
				 HAMPSHIRE_GET_TOUCHED(phampshire->data));
		input_sync(dev);

		phampshire->idx = 0;
	}
}