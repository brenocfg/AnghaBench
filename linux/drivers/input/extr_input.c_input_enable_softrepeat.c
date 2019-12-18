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
struct TYPE_2__ {int /*<<< orphan*/  function; } ;
struct input_dev {int* rep; TYPE_1__ timer; } ;

/* Variables and functions */
 size_t REP_DELAY ; 
 size_t REP_PERIOD ; 
 int /*<<< orphan*/  input_repeat_key ; 

void input_enable_softrepeat(struct input_dev *dev, int delay, int period)
{
	dev->timer.function = input_repeat_key;
	dev->rep[REP_DELAY] = delay;
	dev->rep[REP_PERIOD] = period;
}