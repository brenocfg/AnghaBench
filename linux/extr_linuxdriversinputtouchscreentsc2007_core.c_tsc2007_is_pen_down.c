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
struct tsc2007 {int (* get_pendown_state ) (int /*<<< orphan*/ *) ;TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *) ; 

bool tsc2007_is_pen_down(struct tsc2007 *ts)
{
	/*
	 * NOTE: We can't rely on the pressure to determine the pen down
	 * state, even though this controller has a pressure sensor.
	 * The pressure value can fluctuate for quite a while after
	 * lifting the pen and in some cases may not even settle at the
	 * expected value.
	 *
	 * The only safe way to check for the pen up condition is in the
	 * work function by reading the pen signal state (it's a GPIO
	 * and IRQ). Unfortunately such callback is not always available,
	 * in that case we assume that the pen is down and expect caller
	 * to fall back on the pressure reading.
	 */

	if (!ts->get_pendown_state)
		return true;

	return ts->get_pendown_state(&ts->client->dev);
}