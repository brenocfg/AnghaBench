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
struct input_dev {int /*<<< orphan*/ * rep; int /*<<< orphan*/  (* event ) (struct input_dev*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  INPUT_DO_TOGGLE (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LED ; 
 size_t REP_DELAY ; 
 size_t REP_PERIOD ; 
 int /*<<< orphan*/  SND ; 
 int /*<<< orphan*/  led ; 
 int /*<<< orphan*/  snd ; 
 int /*<<< orphan*/  stub1 (struct input_dev*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct input_dev*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void input_dev_toggle(struct input_dev *dev, bool activate)
{
	if (!dev->event)
		return;

	INPUT_DO_TOGGLE(dev, LED, led, activate);
	INPUT_DO_TOGGLE(dev, SND, snd, activate);

	if (activate && test_bit(EV_REP, dev->evbit)) {
		dev->event(dev, EV_REP, REP_PERIOD, dev->rep[REP_PERIOD]);
		dev->event(dev, EV_REP, REP_DELAY, dev->rep[REP_DELAY]);
	}
}