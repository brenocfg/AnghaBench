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
struct serio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  serio_disconnect_port (struct serio*) ; 
 int /*<<< orphan*/  serio_find_driver (struct serio*) ; 
 int serio_reconnect_driver (struct serio*) ; 

__attribute__((used)) static int serio_reconnect_port(struct serio *serio)
{
	int error = serio_reconnect_driver(serio);

	if (error) {
		serio_disconnect_port(serio);
		serio_find_driver(serio);
	}

	return error;
}