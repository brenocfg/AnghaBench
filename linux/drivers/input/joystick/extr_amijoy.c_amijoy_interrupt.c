#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int joy0dat; int joy1dat; } ;
struct TYPE_3__ {int pra; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TRIGGER ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 TYPE_2__ amiga_custom ; 
 scalar_t__* amijoy ; 
 int /*<<< orphan*/ * amijoy_dev ; 
 TYPE_1__ ciaa ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t amijoy_interrupt(int irq, void *dummy)
{
	int i, data = 0, button = 0;

	for (i = 0; i < 2; i++)
		if (amijoy[i]) {

			switch (i) {
				case 0: data = ~amiga_custom.joy0dat; button = (~ciaa.pra >> 6) & 1; break;
				case 1: data = ~amiga_custom.joy1dat; button = (~ciaa.pra >> 7) & 1; break;
			}

			input_report_key(amijoy_dev[i], BTN_TRIGGER, button);

			input_report_abs(amijoy_dev[i], ABS_X, ((data >> 1) & 1) - ((data >> 9) & 1));
			data = ~(data ^ (data << 1));
			input_report_abs(amijoy_dev[i], ABS_Y, ((data >> 1) & 1) - ((data >> 9) & 1));

			input_sync(amijoy_dev[i]);
		}
	return IRQ_HANDLED;
}