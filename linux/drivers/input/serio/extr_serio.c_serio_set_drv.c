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
struct serio_driver {int dummy; } ;
struct serio {struct serio_driver* drv; } ;

/* Variables and functions */
 int /*<<< orphan*/  serio_continue_rx (struct serio*) ; 
 int /*<<< orphan*/  serio_pause_rx (struct serio*) ; 

__attribute__((used)) static void serio_set_drv(struct serio *serio, struct serio_driver *drv)
{
	serio_pause_rx(serio);
	serio->drv = drv;
	serio_continue_rx(serio);
}