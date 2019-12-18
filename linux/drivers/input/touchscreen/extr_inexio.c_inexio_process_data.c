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
struct inexio {scalar_t__ idx; int /*<<< orphan*/  data; struct input_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 scalar_t__ INEXIO_FORMAT_LENGTH ; 
 int /*<<< orphan*/  INEXIO_GET_TOUCHED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INEXIO_GET_XC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INEXIO_GET_YC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void inexio_process_data(struct inexio *pinexio)
{
	struct input_dev *dev = pinexio->dev;

	if (INEXIO_FORMAT_LENGTH == ++pinexio->idx) {
		input_report_abs(dev, ABS_X, INEXIO_GET_XC(pinexio->data));
		input_report_abs(dev, ABS_Y, INEXIO_GET_YC(pinexio->data));
		input_report_key(dev, BTN_TOUCH, INEXIO_GET_TOUCHED(pinexio->data));
		input_sync(dev);

		pinexio->idx = 0;
	}
}