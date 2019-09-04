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
struct sony_sc {int quirks; } ;

/* Variables and functions */
 int BUZZ_CONTROLLER ; 
 int /*<<< orphan*/  SONY_WORKER_STATE ; 
 int /*<<< orphan*/  buzz_set_leds (struct sony_sc*) ; 
 int /*<<< orphan*/  sony_schedule_work (struct sony_sc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sony_set_leds(struct sony_sc *sc)
{
	if (!(sc->quirks & BUZZ_CONTROLLER))
		sony_schedule_work(sc, SONY_WORKER_STATE);
	else
		buzz_set_leds(sc);
}