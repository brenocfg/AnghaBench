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
struct dynapro {scalar_t__ idx; int /*<<< orphan*/  data; struct input_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 scalar_t__ DYNAPRO_FORMAT_LENGTH ; 
 int /*<<< orphan*/  DYNAPRO_GET_TOUCHED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DYNAPRO_GET_XC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DYNAPRO_GET_YC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void dynapro_process_data(struct dynapro *pdynapro)
{
	struct input_dev *dev = pdynapro->dev;

	if (DYNAPRO_FORMAT_LENGTH == ++pdynapro->idx) {
		input_report_abs(dev, ABS_X, DYNAPRO_GET_XC(pdynapro->data));
		input_report_abs(dev, ABS_Y, DYNAPRO_GET_YC(pdynapro->data));
		input_report_key(dev, BTN_TOUCH,
				 DYNAPRO_GET_TOUCHED(pdynapro->data));
		input_sync(dev);

		pdynapro->idx = 0;
	}
}